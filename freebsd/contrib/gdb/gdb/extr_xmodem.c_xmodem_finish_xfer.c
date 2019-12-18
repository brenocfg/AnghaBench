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
#define  ACK 130 
#define  CANCEL 129 
#define  NAK 128 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int readchar (struct serial*,int) ; 
 int /*<<< orphan*/  serial_write (struct serial*,char*,int) ; 

void
xmodem_finish_xfer (struct serial *desc)
{
  int retries;

  for (retries = 10; retries >= 0; retries--)
    {
      int c;

      serial_write (desc, "\004", 1);	/* Send an EOT */

      c = readchar (desc, 3);
      switch (c)
	{
	case ACK:
	  return;
	case NAK:
	  continue;
	case CANCEL:
	  error ("xmodem_finish_xfer: Transfer aborted by receiver.");
	default:
	  fprintf_unfiltered (gdb_stderr, "xmodem_send_packet: Got unexpected character %c (0%o)\n", c, c);
	  continue;
	}
    }

  error ("xmodem_finish_xfer:  Excessive retries.");
}