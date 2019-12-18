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
struct tmpfs_node {scalar_t__ tn_vpstate; int /*<<< orphan*/ * tn_vnode; scalar_t__ tn_links; scalar_t__ tn_flags; scalar_t__ tn_status; scalar_t__ tn_size; int /*<<< orphan*/  tn_gen; } ;

/* Variables and functions */

__attribute__((used)) static int
tmpfs_node_ctor(void *mem, int size, void *arg, int flags)
{
	struct tmpfs_node *node = (struct tmpfs_node *)mem;

	node->tn_gen++;
	node->tn_size = 0;
	node->tn_status = 0;
	node->tn_flags = 0;
	node->tn_links = 0;
	node->tn_vnode = NULL;
	node->tn_vpstate = 0;

	return (0);
}