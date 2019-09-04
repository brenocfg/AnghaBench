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

__attribute__((used)) static int cmp_ints(const void *v1, const void *v2)
{
	int i1 = *(int *)v1, i2 = *(int *)v2;
	return (i1 < i2) ? -1 : (i1 > i2) ? 1 : 0;
}