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
struct TYPE_2__ {int /*<<< orphan*/  bt; } ;
typedef  TYPE_1__ prof_bt_node_t ;

/* Variables and functions */
 int prof_bt_keycomp (void*,void*) ; 

__attribute__((used)) static bool
prof_bt_node_keycomp(const void *k1, const void *k2) {
	const prof_bt_node_t *bt_node1 = (prof_bt_node_t *)k1;
	const prof_bt_node_t *bt_node2 = (prof_bt_node_t *)k2;
	return prof_bt_keycomp((void *)(&bt_node1->bt),
	    (void *)(&bt_node2->bt));
}