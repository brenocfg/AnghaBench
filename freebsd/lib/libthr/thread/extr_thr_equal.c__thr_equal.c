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
typedef  scalar_t__ pthread_t ;

/* Variables and functions */

int
_thr_equal(pthread_t t1, pthread_t t2)
{
	/* Compare the two thread pointers: */
	return (t1 == t2);
}