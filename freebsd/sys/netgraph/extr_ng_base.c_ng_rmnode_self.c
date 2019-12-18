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
typedef  TYPE_1__* node_p ;
struct TYPE_5__ {int nd_flags; } ;

/* Variables and functions */
 int NGF_CLOSING ; 
 int NGF_INVALID ; 
 TYPE_1__ ng_deadnode ; 
 int /*<<< orphan*/  ng_rmnode ; 
 int ng_send_fn (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ng_rmnode_self(node_p node)
{
	int		error;

	if (node == &ng_deadnode)
		return (0);
	node->nd_flags |= NGF_INVALID;
	if (node->nd_flags & NGF_CLOSING)
		return (0);

	error = ng_send_fn(node, NULL, &ng_rmnode, NULL, 0);
	return (error);
}