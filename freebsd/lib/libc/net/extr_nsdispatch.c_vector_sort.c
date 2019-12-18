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
typedef  int /*<<< orphan*/  vector_comparison ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (void*,unsigned int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vector_sort(void *vec, unsigned int count, size_t esize,
    vector_comparison comparison)
{
	qsort(vec, count, esize, comparison);
}