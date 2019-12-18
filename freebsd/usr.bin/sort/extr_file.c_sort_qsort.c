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
 int /*<<< orphan*/  qsort (void*,size_t,size_t,int (*) (void const*,void const*)) ; 

__attribute__((used)) static int sort_qsort(void *list, size_t count, size_t elem_size,
    int (*cmp_func)(const void *, const void *))
{

	qsort(list, count, elem_size, cmp_func);
	return (0);
}