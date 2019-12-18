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
 int /*<<< orphan*/  __sigev_thread_init ; 
 int /*<<< orphan*/  _pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_threads () ; 
 int /*<<< orphan*/ * sigev_default_thread ; 
 int /*<<< orphan*/  sigev_once ; 

int
__sigev_check_init(void)
{
	if (!have_threads())
		return (-1);

	_pthread_once(&sigev_once, __sigev_thread_init);
	return (sigev_default_thread != NULL) ? 0 : -1;
}