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
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; int /*<<< orphan*/ * mixed; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SPLIT_HOOK_IN ; 
 int /*<<< orphan*/  NG_SPLIT_HOOK_MIXED ; 
 int /*<<< orphan*/  NG_SPLIT_HOOK_OUT ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_split_newhook(node_p node, hook_p hook, const char *name)
{
	priv_p		priv = NG_NODE_PRIVATE(node);
	hook_p		*localhook;

	if (strcmp(name, NG_SPLIT_HOOK_MIXED) == 0) {
		localhook = &priv->mixed;
	} else if (strcmp(name, NG_SPLIT_HOOK_IN) == 0) {
		localhook = &priv->in;
	} else if (strcmp(name, NG_SPLIT_HOOK_OUT) == 0) {
		localhook = &priv->out;
	} else
		return (EINVAL);

	if (*localhook != NULL)
		return (EISCONN);
	*localhook = hook;
	NG_HOOK_SET_PRIVATE(hook, localhook);

	return (0);
}