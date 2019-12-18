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
 int /*<<< orphan*/  prof_bt_hash (void*,size_t*) ; 

__attribute__((used)) static void
prof_bt_node_hash(const void *key, size_t r_hash[2]) {
	const prof_bt_node_t *bt_node = (prof_bt_node_t *)key;
	prof_bt_hash((void *)(&bt_node->bt), r_hash);
}