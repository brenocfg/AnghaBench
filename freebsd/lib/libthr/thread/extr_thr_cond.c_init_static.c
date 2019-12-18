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
struct pthread {int dummy; } ;
typedef  int /*<<< orphan*/ * pthread_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cond_static_lock ; 
 int cond_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
init_static(struct pthread *thread, pthread_cond_t *cond)
{
	int ret;

	THR_LOCK_ACQUIRE(thread, &_cond_static_lock);

	if (*cond == NULL)
		ret = cond_init(cond, NULL);
	else
		ret = 0;

	THR_LOCK_RELEASE(thread, &_cond_static_lock);

	return (ret);
}