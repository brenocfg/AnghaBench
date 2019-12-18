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
typedef  int /*<<< orphan*/  cnd_t ;

/* Variables and functions */
 scalar_t__ pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int thrd_error ; 
 int thrd_success ; 

int
cnd_broadcast(cnd_t *cond)
{

	if (pthread_cond_broadcast(cond) != 0)
		return (thrd_error);
	return (thrd_success);
}