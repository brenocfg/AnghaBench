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
typedef  int /*<<< orphan*/  qsort_block ;

/* Variables and functions */
 scalar_t__ GET_BLOCK_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_r (void*,size_t,size_t,int /*<<< orphan*/ ,int (*) (void*,void const*,void const*)) ; 

void
qsort_b(void *base, size_t nel, size_t width, qsort_block compar)
{
	qsort_r(base, nel, width, compar,
		(int (*)(void *, const void *, const void *))
		GET_BLOCK_FUNCTION(compar));
}