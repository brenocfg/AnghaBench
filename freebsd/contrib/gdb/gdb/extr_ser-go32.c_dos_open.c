#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serial {int fd; } ;
struct dos_ttystate {int fifo; int baudrate; scalar_t__ oflo; scalar_t__ txbusy; scalar_t__ count; scalar_t__ first; TYPE_1__* intrupt; int /*<<< orphan*/  irq; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {struct dos_ttystate* port; } ;

/* Variables and functions */
 int CFCR_8BITS ; 
 int CFCR_DLAB ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int FIFO_ENABLE ; 
 int FIFO_RCV_RST ; 
 int FIFO_TRIGGER ; 
 int FIFO_XMT_RST ; 
 int IER_EMSC ; 
 int IER_ERLS ; 
 int IER_ERXRDY ; 
 int IER_ETXRDY ; 
 int IIR_FIFO_MASK ; 
 int MCR_DTR ; 
 int MCR_IENABLE ; 
 int MCR_RTS ; 
 int /*<<< orphan*/  com_cfcr ; 
 int /*<<< orphan*/  com_data ; 
 int /*<<< orphan*/  com_dlbh ; 
 int /*<<< orphan*/  com_dlbl ; 
 int /*<<< orphan*/  com_fifo ; 
 int /*<<< orphan*/  com_ier ; 
 int /*<<< orphan*/  com_iir ; 
 int /*<<< orphan*/  com_lsr ; 
 int /*<<< orphan*/  com_mcr ; 
 int /*<<< orphan*/  com_msr ; 
 int /*<<< orphan*/  disable () ; 
 int dos_baudconv (int) ; 
 TYPE_1__* dos_hookirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable () ; 
 int /*<<< orphan*/  errno ; 
 int inb (struct dos_ttystate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (struct dos_ttystate*,int /*<<< orphan*/ ,int) ; 
 struct dos_ttystate* ports ; 
 int /*<<< orphan*/  sleep (int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int
dos_open (struct serial *scb, const char *name)
{
  struct dos_ttystate *port;
  int fd, i;

  if (strncasecmp (name, "/dev/", 5) == 0)
    name += 5;
  else if (strncasecmp (name, "\\dev\\", 5) == 0)
    name += 5;

  if (strlen (name) != 4 || strncasecmp (name, "com", 3) != 0)
    {
      errno = ENOENT;
      return -1;
    }

  if (name[3] < '1' || name[3] > '4')
    {
      errno = ENOENT;
      return -1;
    }

  /* FIXME: this is a Bad Idea (tm)!  One should *never* invent file
     handles, since they might be already used by other files/devices.
     The Right Way to do this is to create a real handle by dup()'ing
     some existing one.  */
  fd = name[3] - '1';
  port = &ports[fd];
  if (port->refcnt++ > 0)
    {
      /* Device already opened another user.  Just point at it. */
      scb->fd = fd;
      return 0;
    }

  /* force access to ID reg */
  outb (port, com_cfcr, 0);
  outb (port, com_iir, 0);
  for (i = 0; i < 17; i++)
    {
      if ((inb (port, com_iir) & 0x38) == 0)
	goto ok;
      (void) inb (port, com_data);	/* clear recv */
    }
  errno = ENODEV;
  return -1;

ok:
  /* disable all interrupts in chip */
  outb (port, com_ier, 0);

  /* tentatively enable 16550 fifo, and see if it responds */
  outb (port, com_fifo,
	FIFO_ENABLE | FIFO_RCV_RST | FIFO_XMT_RST | FIFO_TRIGGER);
  sleep (1);
  port->fifo = ((inb (port, com_iir) & IIR_FIFO_MASK) == IIR_FIFO_MASK);

  /* clear pending status reports. */
  (void) inb (port, com_lsr);
  (void) inb (port, com_msr);

  /* enable external interrupt gate (to avoid floating IRQ) */
  outb (port, com_mcr, MCR_IENABLE);

  /* hook up interrupt handler and initialise icu */
  port->intrupt = dos_hookirq (port->irq);
  if (!port->intrupt)
    {
      outb (port, com_mcr, 0);
      outb (port, com_fifo, 0);
      errno = ENODEV;
      return -1;
    }

  disable ();

  /* record port */
  port->intrupt->port = port;
  scb->fd = fd;

  /* clear rx buffer, tx busy flag and overflow count */
  port->first = port->count = 0;
  port->txbusy = 0;
  port->oflo = 0;

  /* set default baud rate and mode: 9600,8,n,1 */
  i = dos_baudconv (port->baudrate = 9600);
  outb (port, com_cfcr, CFCR_DLAB);
  outb (port, com_dlbl, i & 0xff);
  outb (port, com_dlbh, i >> 8);
  outb (port, com_cfcr, CFCR_8BITS);

  /* enable all interrupts */
  outb (port, com_ier, IER_ETXRDY | IER_ERXRDY | IER_ERLS | IER_EMSC);

  /* enable DTR & RTS */
  outb (port, com_mcr, MCR_DTR | MCR_RTS | MCR_IENABLE);

  enable ();

  return 0;
}