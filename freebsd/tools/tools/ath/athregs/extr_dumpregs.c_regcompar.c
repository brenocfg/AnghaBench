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
struct dumpreg {int addr; } ;

/* Variables and functions */

__attribute__((used)) static int
regcompar(const void *a, const void *b)
{
	const struct dumpreg *ra = *(const struct dumpreg **)a;
	const struct dumpreg *rb = *(const struct dumpreg **)b;
	return ra->addr - rb->addr;
}