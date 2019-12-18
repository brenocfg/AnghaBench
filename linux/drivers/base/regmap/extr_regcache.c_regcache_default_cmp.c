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
struct reg_default {int reg; } ;

/* Variables and functions */

__attribute__((used)) static int regcache_default_cmp(const void *a, const void *b)
{
	const struct reg_default *_a = a;
	const struct reg_default *_b = b;

	return _a->reg - _b->reg;
}