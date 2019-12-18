#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct serial {size_t fd; } ;
struct intrupt {int /*<<< orphan*/  port; } ;
struct dos_ttystate {int /*<<< orphan*/  baudrate; scalar_t__ fifo; scalar_t__ oflo; struct intrupt* intrupt; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  com_fifo ; 
 int /*<<< orphan*/  com_ier ; 
 int /*<<< orphan*/  com_mcr ; 
 int /*<<< orphan*/  disable () ; 
 int /*<<< orphan*/  dos_unhookirq (struct intrupt*) ; 
 int /*<<< orphan*/  enable () ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  outb (struct dos_ttystate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dos_ttystate* ports ; 

__attribute__((used)) static void
dos_close (struct serial *scb)
{
  struct dos_ttystate *port;
  struct intrupt *intrupt;

  if (!scb)
    return;

  port = &ports[scb->fd];

  if (port->refcnt-- > 1)
    return;

  if (!(intrupt = port->intrupt))
    return;

  /* disable interrupts, fifo, flow control */
  disable ();
  port->intrupt = 0;
  intrupt->port = 0;
  outb (port, com_fifo, 0);
  outb (port, com_ier, 0);
  enable ();

  /* unhook handler, and disable interrupt gate */
  dos_unhookirq (intrupt);
  outb (port, com_mcr, 0);

  /* Check for overflow errors */
  if (port->oflo)
    {
      fprintf_unfiltered (gdb_stderr,
			  "Serial input overruns occurred.\n");
      fprintf_unfiltered (gdb_stderr, "This system %s handle %d baud.\n",
			  port->fifo ? "cannot" : "needs a 16550 to",
			  port->baudrate);
    }
}