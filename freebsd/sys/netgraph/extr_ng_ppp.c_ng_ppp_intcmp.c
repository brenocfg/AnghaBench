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

__attribute__((used)) static int
ng_ppp_intcmp(void *latency, const void *v1, const void *v2)
{
	const int index1 = *((const int *) v1);
	const int index2 = *((const int *) v2);

	return ((int *)latency)[index1] - ((int *)latency)[index2];
}