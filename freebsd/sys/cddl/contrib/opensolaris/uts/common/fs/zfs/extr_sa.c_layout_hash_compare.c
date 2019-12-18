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
struct TYPE_2__ {int /*<<< orphan*/  lot_instance; int /*<<< orphan*/  lot_hash; } ;
typedef  TYPE_1__ sa_lot_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
layout_hash_compare(const void *arg1, const void *arg2)
{
	const sa_lot_t *node1 = (const sa_lot_t *)arg1;
	const sa_lot_t *node2 = (const sa_lot_t *)arg2;

	int cmp = AVL_CMP(node1->lot_hash, node2->lot_hash);
	if (likely(cmp))
		return (cmp);

	return (AVL_CMP(node1->lot_instance, node2->lot_instance));
}