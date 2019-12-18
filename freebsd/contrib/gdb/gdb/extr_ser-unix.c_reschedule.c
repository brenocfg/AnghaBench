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
struct serial {int async_state; int /*<<< orphan*/  fd; int /*<<< orphan*/  bufcnt; } ;

/* Variables and functions */
#define  FD_SCHEDULED 129 
#define  NOTHING_SCHEDULED 128 
 int /*<<< orphan*/  add_file_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct serial*) ; 
 int create_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct serial*) ; 
 int /*<<< orphan*/  delete_file_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_timer (int) ; 
 int /*<<< orphan*/  fd_event ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  push_event ; 
 scalar_t__ serial_debug_p (struct serial*) ; 
 scalar_t__ serial_is_async_p (struct serial*) ; 

__attribute__((used)) static void
reschedule (struct serial *scb)
{
  if (serial_is_async_p (scb))
    {
      int next_state;
      switch (scb->async_state)
	{
	case FD_SCHEDULED:
	  if (scb->bufcnt == 0)
	    next_state = FD_SCHEDULED;
	  else
	    {
	      delete_file_handler (scb->fd);
	      next_state = create_timer (0, push_event, scb);
	    }
	  break;
	case NOTHING_SCHEDULED:
	  if (scb->bufcnt == 0)
	    {
	      add_file_handler (scb->fd, fd_event, scb);
	      next_state = FD_SCHEDULED;
	    }
	  else
	    {
	      next_state = create_timer (0, push_event, scb);
	    }
	  break;
	default: /* TIMER SCHEDULED */
	  if (scb->bufcnt == 0)
	    {
	      delete_timer (scb->async_state);
	      add_file_handler (scb->fd, fd_event, scb);
	      next_state = FD_SCHEDULED;
	    }
	  else
	    next_state = scb->async_state;
	  break;
	}
      if (serial_debug_p (scb))
	{
	  switch (next_state)
	    {
	    case FD_SCHEDULED:
	      if (scb->async_state != FD_SCHEDULED)
		fprintf_unfiltered (gdb_stdlog, "[fd%d->fd-scheduled]\n",
				    scb->fd);
	      break;
	    default: /* TIMER SCHEDULED */
	      if (scb->async_state == FD_SCHEDULED)
		fprintf_unfiltered (gdb_stdlog, "[fd%d->timer-scheduled]\n",
				    scb->fd);
	      break;
	    }
	}
      scb->async_state = next_state;
    }
}