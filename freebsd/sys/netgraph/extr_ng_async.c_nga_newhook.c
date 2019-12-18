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
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_3__ {scalar_t__ sync; scalar_t__ async; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_ASYNC_HOOK_ASYNC ; 
 int /*<<< orphan*/  NG_ASYNC_HOOK_SYNC ; 
 int /*<<< orphan*/  NG_HOOK_FORCE_WRITER (scalar_t__) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nga_newhook(node_p node, hook_p hook, const char *name)
{
	const sc_p sc = NG_NODE_PRIVATE(node);
	hook_p *hookp;

	if (!strcmp(name, NG_ASYNC_HOOK_ASYNC)) {
		/*
		 * We use a static buffer here so only one packet
		 * at a time can be allowed to travel in this direction.
		 * Force Writer semantics.
		 */
		NG_HOOK_FORCE_WRITER(hook);
		hookp = &sc->async;
	} else if (!strcmp(name, NG_ASYNC_HOOK_SYNC)) {
		/*
		 * We use a static state here so only one packet
		 * at a time can be allowed to travel in this direction.
		 * Force Writer semantics.
		 * Since we set this for both directions
		 * we might as well set it for the whole node
		 * bit I haven;t done that (yet).
		 */
		NG_HOOK_FORCE_WRITER(hook);
		hookp = &sc->sync;
	} else {
		return (EINVAL);
	}
	if (*hookp) /* actually can't happen I think [JRE] */
		return (EISCONN);
	*hookp = hook;
	return (0);
}