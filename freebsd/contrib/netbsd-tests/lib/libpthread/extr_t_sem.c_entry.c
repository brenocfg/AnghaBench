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
typedef  int /*<<< orphan*/  sem_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
entry(void * a_arg)
{
	pthread_t self = pthread_self();
	sem_t *semp = (sem_t *) a_arg;

	printf("Thread %p waiting for semaphore...\n", self);
	sem_wait(semp);
	printf("Thread %p got semaphore\n", self);

	return NULL;
}