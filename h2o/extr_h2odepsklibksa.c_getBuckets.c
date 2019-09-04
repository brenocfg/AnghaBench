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
typedef  size_t saint_t ;

/* Variables and functions */

__attribute__((used)) static inline void getBuckets(const saint_t *C, saint_t *B, saint_t k, saint_t end)
{
	saint_t i, sum = 0;
	if (end) for (i = 0; i < k; ++i) sum += C[i], B[i] = sum;
	else for (i = 0; i < k; ++i) sum += C[i], B[i] = sum - C[i];
}