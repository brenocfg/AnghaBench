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
struct dos_ttystate {int baudrate; } ;

/* Variables and functions */
 unsigned char CFCR_DLAB ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  com_cfcr ; 
 int /*<<< orphan*/  com_dlbh ; 
 int /*<<< orphan*/  com_dlbl ; 
 int /*<<< orphan*/  disable () ; 
 int dos_baudconv (int) ; 
 int /*<<< orphan*/  enable () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 unsigned char inb (struct dos_ttystate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (struct dos_ttystate*,int /*<<< orphan*/ ,unsigned char) ; 
 struct dos_ttystate* ports ; 

__attribute__((used)) static int
dos_setbaudrate (struct serial *scb, int rate)
{
  struct dos_ttystate *port = &ports[scb->fd];

  if (port->baudrate != rate)
    {
      int x;
      unsigned char cfcr;

      x = dos_baudconv (rate);
      if (x <= 0)
	{
	  fprintf_unfiltered (gdb_stderr, "%d: impossible baudrate\n", rate);
	  errno = EINVAL;
	  return -1;
	}

      disable ();
      cfcr = inb (port, com_cfcr);

      outb (port, com_cfcr, CFCR_DLAB);
      outb (port, com_dlbl, x & 0xff);
      outb (port, com_dlbh, x >> 8);
      outb (port, com_cfcr, cfcr);
      port->baudrate = rate;
      enable ();
    }

  return 0;
}