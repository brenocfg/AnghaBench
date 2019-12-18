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
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  random_reseed_mtx ; 
 scalar_t__ thrd_busy ; 
 int /*<<< orphan*/  thrd_exit (int /*<<< orphan*/ ) ; 

void
randomdev_unblock(void)
{

#if 0
	if (mtx_trylock(&random_reseed_mtx) == thrd_busy)
		printf("Mutex held. Good.\n");
	else {
		printf("Mutex not held. PANIC!!\n");
		thrd_exit(0);
	}
#endif
	printf("random: unblocking device.\n");
}