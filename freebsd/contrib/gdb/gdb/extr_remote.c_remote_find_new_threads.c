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

/* Variables and functions */
 int /*<<< orphan*/  CRAZY_MAX_THREADS ; 
 scalar_t__ MAGIC_NULL_PID ; 
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  remote_current_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_newthread_step ; 
 int /*<<< orphan*/  remote_threadlist_iterator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remote_find_new_threads (void)
{
  remote_threadlist_iterator (remote_newthread_step, 0,
			      CRAZY_MAX_THREADS);
  if (PIDGET (inferior_ptid) == MAGIC_NULL_PID)	/* ack ack ack */
    inferior_ptid = remote_current_thread (inferior_ptid);
}