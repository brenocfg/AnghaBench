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
struct mac_biba {int mb_flags; int /*<<< orphan*/  mb_rangehigh; int /*<<< orphan*/  mb_rangelow; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_BIBA_FLAG_RANGE ; 

__attribute__((used)) static void
biba_copy_range(struct mac_biba *labelfrom, struct mac_biba *labelto)
{

	KASSERT((labelfrom->mb_flags & MAC_BIBA_FLAG_RANGE) != 0,
	    ("biba_copy_range: labelfrom not range"));

	labelto->mb_rangelow = labelfrom->mb_rangelow;
	labelto->mb_rangehigh = labelfrom->mb_rangehigh;
	labelto->mb_flags |= MAC_BIBA_FLAG_RANGE;
}