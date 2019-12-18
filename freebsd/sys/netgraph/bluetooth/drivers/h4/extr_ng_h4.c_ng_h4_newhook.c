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
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_1__* ng_h4_info_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_4__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_H4_HOOK ; 
 int /*<<< orphan*/  NG_H4_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_H4_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_h4_newhook(node_p node, hook_p hook, const char *name)
{
	ng_h4_info_p	sc = (ng_h4_info_p) NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_H4_HOOK) != 0)
		return (EINVAL);

	NG_H4_LOCK(sc);

	if (sc->hook != NULL) {
		NG_H4_UNLOCK(sc);
		return (EISCONN);
	}
	sc->hook = hook;

	NG_H4_UNLOCK(sc);

	return (0);
}