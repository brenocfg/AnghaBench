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
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cuse_dev ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_mtx ; 
 int /*<<< orphan*/  cuse_server_head ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
cuse_kern_uninit(void *arg)
{
	void *ptr;

	while (1) {

		printf("Cuse: Please exit all /dev/cuse instances "
		    "and processes which have used this device.\n");

		pause("DRAIN", 2 * hz);

		cuse_lock();
		ptr = TAILQ_FIRST(&cuse_server_head);
		cuse_unlock();

		if (ptr == NULL)
			break;
	}

	if (cuse_dev != NULL)
		destroy_dev(cuse_dev);

	mtx_destroy(&cuse_mtx);
}