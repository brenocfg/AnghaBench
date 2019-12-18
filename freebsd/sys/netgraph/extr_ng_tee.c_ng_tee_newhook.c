#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_2__* hi_p ;
struct TYPE_6__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  hook; struct TYPE_6__* dest; struct TYPE_6__* dup; } ;
struct TYPE_5__ {TYPE_2__ left; TYPE_2__ left2right; TYPE_2__ right; TYPE_2__ right2left; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_TEE_HOOK_LEFT ; 
 int /*<<< orphan*/  NG_TEE_HOOK_LEFT2RIGHT ; 
 int /*<<< orphan*/  NG_TEE_HOOK_RIGHT ; 
 int /*<<< orphan*/  NG_TEE_HOOK_RIGHT2LEFT ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_tee_newhook(node_p node, hook_p hook, const char *name)
{
	sc_p	privdata = NG_NODE_PRIVATE(node);
	hi_p	hinfo;

	/* Precalculate internal paths. */
	if (strcmp(name, NG_TEE_HOOK_RIGHT) == 0) {
		hinfo = &privdata->right;
		if (privdata->left.dest)
			privdata->left.dup = privdata->left.dest;
		privdata->left.dest = hinfo;
		privdata->right2left.dest = hinfo;
	} else if (strcmp(name, NG_TEE_HOOK_LEFT) == 0) {
		hinfo = &privdata->left;
		if (privdata->right.dest)
			privdata->right.dup = privdata->right.dest;
		privdata->right.dest = hinfo;
		privdata->left2right.dest = hinfo;
	} else if (strcmp(name, NG_TEE_HOOK_RIGHT2LEFT) == 0) {
		hinfo = &privdata->right2left;
		if (privdata->right.dest)
			privdata->right.dup = hinfo;
		else    
			privdata->right.dest = hinfo;
	} else if (strcmp(name, NG_TEE_HOOK_LEFT2RIGHT) == 0) {
		hinfo = &privdata->left2right;
		if (privdata->left.dest)
			privdata->left.dup = hinfo;
		else
			privdata->left.dest = hinfo;
	} else
		return (EINVAL);
	hinfo->hook = hook;
	bzero(&hinfo->stats, sizeof(hinfo->stats));
	NG_HOOK_SET_PRIVATE(hook, hinfo);
	return (0);
}