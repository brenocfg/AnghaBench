#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  td_thragent_t ;
struct TYPE_4__ {scalar_t__ bptaddr; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ td_notify_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  create_thread_event_breakpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  gdbarch_convert_from_func_ptr_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ td_ta_event_addr_p (int /*<<< orphan*/ *,int,TYPE_2__*) ; 

__attribute__((used)) static td_err_e
enable_thread_event (td_thragent_t *thread_agent, int event, CORE_ADDR *bp)
{
  td_notify_t notify;
  td_err_e err;

  /* Get the breakpoint address for thread EVENT.  */
  err = td_ta_event_addr_p (thread_agent, event, &notify);
  if (err != TD_OK)
    return err;

  /* Set up the breakpoint.  */
  (*bp) = gdbarch_convert_from_func_ptr_addr (current_gdbarch,
					      (CORE_ADDR) notify.u.bptaddr,
					      &current_target);
  create_thread_event_breakpoint ((*bp));

  return TD_OK;
}