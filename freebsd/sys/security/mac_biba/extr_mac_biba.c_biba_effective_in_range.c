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
struct mac_biba {int mb_flags; int /*<<< orphan*/  mb_rangelow; int /*<<< orphan*/  mb_effective; int /*<<< orphan*/  mb_rangehigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 int MAC_BIBA_FLAG_RANGE ; 
 scalar_t__ biba_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
biba_effective_in_range(struct mac_biba *effective, struct mac_biba *range)
{

	KASSERT((effective->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) != 0,
	    ("biba_effective_in_range: a not effective"));
	KASSERT((range->mb_flags & MAC_BIBA_FLAG_RANGE) != 0,
	    ("biba_effective_in_range: b not range"));

	return (biba_dominate_element(&range->mb_rangehigh,
	    &effective->mb_effective) &&
	    biba_dominate_element(&effective->mb_effective,
	    &range->mb_rangelow));

	return (1);
}