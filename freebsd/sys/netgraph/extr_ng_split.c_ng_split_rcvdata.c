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
typedef  TYPE_1__* priv_p ;
typedef  scalar_t__ item_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * mixed; int /*<<< orphan*/ * in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_FREE_ITEM (scalar_t__) ; 
 int /*<<< orphan*/  NG_FWD_ITEM_HOOK (int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ng_split_rcvdata(hook_p hook, item_p item)
{
	const priv_p	priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	int		error = 0;

	if (hook == priv->out) {
		printf("ng_split: got packet from out hook!\n");
		NG_FREE_ITEM(item);
		error = EINVAL;
	} else if ((hook == priv->in) && (priv->mixed != NULL)) {
		NG_FWD_ITEM_HOOK(error, item, priv->mixed);
	} else if ((hook == priv->mixed) && (priv->out != NULL)) {
		NG_FWD_ITEM_HOOK(error, item, priv->out);
	}

	if (item)
		NG_FREE_ITEM(item);

	return (error);
}