#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ ctl_named_node_t ;

/* Variables and functions */
 TYPE_1__* ctl_named_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const ctl_named_node_t *
ctl_named_children(const ctl_named_node_t *node, size_t index) {
	const ctl_named_node_t *children = ctl_named_node(node->children);

	return (children ? &children[index] : NULL);
}