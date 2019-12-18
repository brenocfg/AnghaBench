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
 int i ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  sleep (int) ; 

void *
foo2(void *arg)
{
	printf("thread %p, &i = %p\n", pthread_self(), &i);
	for (i = 10; i > 0; i--) {
		printf("thread %p, i = %d\n", pthread_self(), i);
		sleep(1);
	}
	return (NULL);
}