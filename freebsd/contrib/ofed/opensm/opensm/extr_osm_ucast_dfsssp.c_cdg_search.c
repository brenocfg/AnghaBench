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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ channelID; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ cdg_node_t ;

/* Variables and functions */

__attribute__((used)) static cdg_node_t *cdg_search(cdg_node_t * root, uint64_t channelID)
{
	while (root) {
		if (channelID < root->channelID)
			root = root->left;
		else if (channelID > root->channelID)
			root = root->right;
		else if (channelID == root->channelID)
			return root;
	}
	return NULL;
}