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
struct sparc64_dump_reg {scalar_t__ dr_pa; scalar_t__ dr_size; } ;

/* Variables and functions */

__attribute__((used)) static int
_sparc64_reg_cmp(const void *a, const void *b)
{
	const struct sparc64_dump_reg *ra, *rb;

	ra = a;
	rb = b;
	if (ra->dr_pa < rb->dr_pa)
		return (-1);
	else if (ra->dr_pa >= rb->dr_pa + rb->dr_size)
		return (1);
	else
		return (0);
}