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
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int pthread_cond_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evthread_posix_cond_signal(void *cond_, int broadcast)
{
	pthread_cond_t *cond = cond_;
	int r;
	if (broadcast)
		r = pthread_cond_broadcast(cond);
	else
		r = pthread_cond_signal(cond);
	return r ? -1 : 0;
}