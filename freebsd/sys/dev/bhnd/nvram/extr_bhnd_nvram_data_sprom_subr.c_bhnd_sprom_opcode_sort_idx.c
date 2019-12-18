#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ vid; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */

__attribute__((used)) static int
bhnd_sprom_opcode_sort_idx(const void *lhs, const void *rhs)
{
	const bhnd_sprom_opcode_idx_entry *l, *r;

	l = lhs;
	r = rhs;

	if (l->vid < r->vid)
		return (-1);
	if (l->vid > r->vid)
		return (1);
	return (0);
}