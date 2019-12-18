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

/* Variables and functions */
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
hthread(void *arg)
{
	sem_t *semmarit = arg;

	for (;;) {
		sem_post(&semmarit[2]);
		sem_wait(&semmarit[1]);
		sem_wait(&semmarit[0]);
	}

	return NULL;
}