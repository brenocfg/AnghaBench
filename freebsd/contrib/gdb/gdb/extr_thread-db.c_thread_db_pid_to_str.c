#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ti_state; scalar_t__ ti_lid; scalar_t__ ti_tid; } ;
typedef  TYPE_2__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_err_e ;
struct thread_info {TYPE_1__* private; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {char* (* to_pid_to_str ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  th_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_THR_ACTIVE ; 
 struct thread_info* find_thread_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 char* normal_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long,...) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 
 char* stub2 (int /*<<< orphan*/ ) ; 
 TYPE_4__* target_beneath ; 
 TYPE_2__* thread_db_get_info (struct thread_info*) ; 
 int /*<<< orphan*/  thread_db_map_id2thr (struct thread_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_db_state_str (scalar_t__) ; 

__attribute__((used)) static char *
thread_db_pid_to_str (ptid_t ptid)
{
  if (is_thread (ptid))
    {
      static char buf[64];
      td_thrinfo_t *ti_p;
      td_err_e err;
      struct thread_info *thread_info;

      thread_info = find_thread_pid (ptid);
      thread_db_map_id2thr (thread_info, 0);
      if (!thread_info->private->th_valid)
	{
	  snprintf (buf, sizeof (buf), "Thread %ld (Missing)",
		    GET_THREAD (ptid));
	  return buf;
	}

      ti_p = thread_db_get_info (thread_info);

      if (ti_p->ti_state == TD_THR_ACTIVE && ti_p->ti_lid != 0)
	{
	  snprintf (buf, sizeof (buf), "Thread %ld (LWP %d)",
		    (long) ti_p->ti_tid, ti_p->ti_lid);
	}
      else
	{
	  snprintf (buf, sizeof (buf), "Thread %ld (%s)",
		    (long) ti_p->ti_tid,
		    thread_db_state_str (ti_p->ti_state));
	}

      return buf;
    }

  if (target_beneath->to_pid_to_str (ptid))
    return target_beneath->to_pid_to_str (ptid);

  return normal_pid_to_str (ptid);
}