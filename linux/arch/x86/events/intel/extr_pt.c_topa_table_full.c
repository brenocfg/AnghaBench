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
struct topa {int last; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 int TENTS_PER_PAGE ; 
 int /*<<< orphan*/  intel_pt_validate_hw_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool topa_table_full(struct topa *topa)
{
	/* single-entry ToPA is a special case */
	if (!intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		return !!topa->last;

	return topa->last == TENTS_PER_PAGE - 1;
}