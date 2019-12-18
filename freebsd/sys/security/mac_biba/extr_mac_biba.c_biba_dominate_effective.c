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
struct mac_biba {int mb_flags; int /*<<< orphan*/  mb_effective; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 int biba_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
biba_dominate_effective(struct mac_biba *a, struct mac_biba *b)
{
	KASSERT((a->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) != 0,
	    ("biba_dominate_effective: a not effective"));
	KASSERT((b->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) != 0,
	    ("biba_dominate_effective: b not effective"));

	return (biba_dominate_element(&a->mb_effective, &b->mb_effective));
}