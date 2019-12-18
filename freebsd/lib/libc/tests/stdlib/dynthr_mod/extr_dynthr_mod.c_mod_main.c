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
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  mod_thread ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thr ; 

void
mod_main(int op)
{
	int rc;

	switch (op) {
	case 1:
		rc = pthread_create(&thr, NULL, mod_thread, NULL);
		if (rc != 0)
			_exit(1);
		break;
	case 0:
		pthread_join(thr, NULL);
		break;
	}
}