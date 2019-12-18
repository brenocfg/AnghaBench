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
typedef  int /*<<< orphan*/  mtx_t ;
typedef  int /*<<< orphan*/  cnd_t ;

/* Variables and functions */
 scalar_t__ pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int thrd_error ; 
 int thrd_success ; 

int
cnd_wait(cnd_t *cond, mtx_t *mtx)
{

	if (pthread_cond_wait(cond, mtx) != 0)
		return (thrd_error);
	return (thrd_success);
}