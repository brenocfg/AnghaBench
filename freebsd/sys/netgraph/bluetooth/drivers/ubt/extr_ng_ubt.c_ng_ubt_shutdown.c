#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* node_p ;
struct TYPE_6__ {int nd_flags; } ;

/* Variables and functions */
 int NGF_REALLY_DIE ; 
 int /*<<< orphan*/  NG_NODE_REVIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (TYPE_1__*) ; 

__attribute__((used)) static int
ng_ubt_shutdown(node_p node)
{
	if (node->nd_flags & NGF_REALLY_DIE) {
		/*
                 * We came here because the USB device is being
		 * detached, so stop being persistent.
                 */
		NG_NODE_SET_PRIVATE(node, NULL);
		NG_NODE_UNREF(node);
	} else
		NG_NODE_REVIVE(node); /* tell ng_rmnode we are persisant */

	return (0);
}