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
struct serial {int async_state; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  FD_SCHEDULED 129 
#define  NOTHING_SCHEDULED 128 
 int /*<<< orphan*/  delete_file_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_timer (int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  reschedule (struct serial*) ; 
 scalar_t__ serial_debug_p (struct serial*) ; 

void
ser_unix_async (struct serial *scb,
		int async_p)
{
  if (async_p)
    {
      /* Force a re-schedule. */
      scb->async_state = NOTHING_SCHEDULED;
      if (serial_debug_p (scb))
	fprintf_unfiltered (gdb_stdlog, "[fd%d->asynchronous]\n",
			    scb->fd);
      reschedule (scb);
    }
  else
    {
      if (serial_debug_p (scb))
	fprintf_unfiltered (gdb_stdlog, "[fd%d->synchronous]\n",
			    scb->fd);
      /* De-schedule whatever tasks are currently scheduled. */
      switch (scb->async_state)
	{
	case FD_SCHEDULED:
	  delete_file_handler (scb->fd);
	  break;
	case NOTHING_SCHEDULED:
	  break;
	default: /* TIMER SCHEDULED */
	  delete_timer (scb->async_state);
	  break;
	}
    }
}