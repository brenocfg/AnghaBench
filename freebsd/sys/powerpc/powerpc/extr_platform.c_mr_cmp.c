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
struct mem_region {scalar_t__ mr_start; } ;

/* Variables and functions */

__attribute__((used)) static int
mr_cmp(const void *a, const void *b)
{
	const struct mem_region *regiona, *regionb;

	regiona = a;
	regionb = b;
	if (regiona->mr_start < regionb->mr_start)
		return (-1);
	else if (regiona->mr_start > regionb->mr_start)
		return (1);
	else
		return (0);
}