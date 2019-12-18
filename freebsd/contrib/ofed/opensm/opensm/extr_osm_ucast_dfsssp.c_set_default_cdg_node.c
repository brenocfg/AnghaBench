#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/ * pre; scalar_t__ visited; int /*<<< orphan*/  status; int /*<<< orphan*/ * linklist; scalar_t__ channelID; } ;
typedef  TYPE_1__ cdg_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN ; 

__attribute__((used)) static inline void set_default_cdg_node(cdg_node_t * node)
{
	node->channelID = 0;
	node->linklist = NULL;
	node->status = UNKNOWN;
	node->visited = 0;
	node->pre = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
}