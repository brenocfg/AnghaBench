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
struct serial {int dummy; } ;

/* Variables and functions */
#define  CANCEL 129 
#define  NAK 128 
 int blknum ; 
 int crcflag ; 
 int /*<<< orphan*/  crcinit () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int readchar (struct serial*,int) ; 

int
xmodem_init_xfer (struct serial *desc)
{
  int c;
  int i;

  blknum = 1;
  crcflag = 0;
  crcinit ();

  for (i = 1; i <= 10; i++)
    {
      c = readchar (desc, 6);

      switch (c)
	{
	case 'C':
	  crcflag = 1;
	case NAK:
	  return 0;
	default:
	  fprintf_unfiltered (gdb_stderr, "xmodem_init_xfer: Got unexpected character %c (0%o)\n", c, c);
	  continue;
	case CANCEL:		/* target aborted load */
	  fprintf_unfiltered (gdb_stderr, "Got a CANCEL from the target.\n");
	  continue;
	}
    }
  error ("xmodem_init_xfer:  Too many unexpected characters.");
}