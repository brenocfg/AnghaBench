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
typedef  int /*<<< orphan*/  tss_t ;

/* Variables and functions */
 scalar_t__ pthread_setspecific (int /*<<< orphan*/ ,void*) ; 
 int thrd_error ; 
 int thrd_success ; 

int
tss_set(tss_t key, void *val)
{

	if (pthread_setspecific(key, val) != 0)
		return (thrd_error);
	return (thrd_success);
}