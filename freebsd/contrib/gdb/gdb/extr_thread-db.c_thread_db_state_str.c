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
typedef  int td_thr_state_e ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  TD_THR_ACTIVE 133 
#define  TD_THR_RUN 132 
#define  TD_THR_SLEEP 131 
#define  TD_THR_STOPPED 130 
#define  TD_THR_STOPPED_ASLEEP 129 
#define  TD_THR_ZOMBIE 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *
thread_db_state_str (td_thr_state_e state)
{
  static char buf[64];

  switch (state)
    {
    case TD_THR_STOPPED:
      return "stopped by debugger";
    case TD_THR_RUN:
      return "runnable";
    case TD_THR_ACTIVE:
      return "active";
    case TD_THR_ZOMBIE:
      return "zombie";
    case TD_THR_SLEEP:
      return "sleeping";
    case TD_THR_STOPPED_ASLEEP:
      return "stopped by debugger AND blocked";
    default:
      snprintf (buf, sizeof (buf), "unknown thread_db state %d", state);
      return buf;
    }
}