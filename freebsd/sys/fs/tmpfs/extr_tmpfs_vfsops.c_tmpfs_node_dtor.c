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
struct tmpfs_node {int /*<<< orphan*/  tn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNON ; 

__attribute__((used)) static void
tmpfs_node_dtor(void *mem, int size, void *arg)
{
	struct tmpfs_node *node = (struct tmpfs_node *)mem;
	node->tn_type = VNON;
}