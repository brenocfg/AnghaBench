#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_3__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/  exit; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* gp_timer_prov ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void __cl_timer_prov_destroy(void)
{
	pthread_t tid;

	if (!gp_timer_prov)
		return;

	tid = gp_timer_prov->thread;
	pthread_mutex_lock(&gp_timer_prov->mutex);
	gp_timer_prov->exit = TRUE;
	pthread_cond_broadcast(&gp_timer_prov->cond);
	pthread_mutex_unlock(&gp_timer_prov->mutex);
	pthread_join(tid, NULL);

	/* Destroy the mutex and condition variable. */
	pthread_mutex_destroy(&gp_timer_prov->mutex);
	pthread_cond_destroy(&gp_timer_prov->cond);

	/* Free the memory and reset the global pointer. */
	free(gp_timer_prov);
	gp_timer_prov = NULL;
}