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
 int /*<<< orphan*/  cv ; 
 int /*<<< orphan*/  m ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_yield () ; 
 scalar_t__ stop ; 
 scalar_t__ wake ; 

void *
thr_routine(void *arg)
{
	pthread_mutex_lock(&m);
	while (wake == 0)
		pthread_cond_wait(&cv, &m);
	pthread_mutex_unlock(&m);

	while (stop == 0)
		pthread_yield();
	return (NULL);
}