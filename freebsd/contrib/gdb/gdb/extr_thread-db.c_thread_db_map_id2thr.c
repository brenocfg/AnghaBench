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
typedef  scalar_t__ td_err_e ;
struct thread_info {TYPE_1__* private; int /*<<< orphan*/  ptid; } ;
struct TYPE_2__ {int th_valid; int /*<<< orphan*/  th; } ;

/* Variables and functions */
 scalar_t__ GET_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  error (char*,long,char*) ; 
 scalar_t__ td_ta_map_id2thr_p (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 
 char* thread_db_err_str (scalar_t__) ; 

__attribute__((used)) static void
thread_db_map_id2thr (struct thread_info *thread_info, int fatal)
{
  td_err_e err;

  if (thread_info->private->th_valid)
    return;

  err = td_ta_map_id2thr_p (thread_agent, GET_THREAD (thread_info->ptid),
			    &thread_info->private->th);
  if (err != TD_OK)
    {
      if (fatal)
	error ("Cannot find thread %ld: %s",
	       (long) GET_THREAD (thread_info->ptid),
	       thread_db_err_str (err));
    }
  else
    thread_info->private->th_valid = 1;
}