#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ typecookie; scalar_t__ cmd; } ;
struct ng_mesg {TYPE_1__ header; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_5__ {int persistent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 scalar_t__ NGM_HUB_COOKIE ; 
 scalar_t__ NGM_HUB_SET_PERSISTENT ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_hub_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	int error = 0;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	if (msg->header.typecookie == NGM_HUB_COOKIE &&
	    msg->header.cmd == NGM_HUB_SET_PERSISTENT) {
		priv->persistent = 1;
	} else {
		error = EINVAL;
	}

	NG_FREE_MSG(msg);
	return (error);
}