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
struct bidirectional_transfer_state {int /*<<< orphan*/  ptg; int /*<<< orphan*/  gtp; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int tloop_join (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udt_copy_task_routine ; 

__attribute__((used)) static int tloop_spawnwait_tasks(struct bidirectional_transfer_state *s)
{
	pthread_t gtp_thread;
	pthread_t ptg_thread;
	int err;
	int ret = 0;
	err = pthread_create(&gtp_thread, NULL, udt_copy_task_routine,
		&s->gtp);
	if (err)
		die(_("can't start thread for copying data: %s"), strerror(err));
	err = pthread_create(&ptg_thread, NULL, udt_copy_task_routine,
		&s->ptg);
	if (err)
		die(_("can't start thread for copying data: %s"), strerror(err));

	ret |= tloop_join(gtp_thread, "Git to program copy");
	ret |= tloop_join(ptg_thread, "Program to git copy");
	return ret;
}