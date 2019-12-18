#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ub_timestamp; int /*<<< orphan*/  ub_txg; } ;
typedef  TYPE_1__ uberblock_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
vdev_uberblock_compare(const uberblock_t *ub1, const uberblock_t *ub2)
{
	int cmp = AVL_CMP(ub1->ub_txg, ub2->ub_txg);
	if (likely(cmp))
		return (cmp);

	return (AVL_CMP(ub1->ub_timestamp, ub2->ub_timestamp));
}