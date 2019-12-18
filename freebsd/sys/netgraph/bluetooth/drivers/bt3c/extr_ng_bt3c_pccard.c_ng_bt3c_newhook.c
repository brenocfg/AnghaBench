#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_2__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_BT3C_HOOK ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bt3c_newhook(node_p node, hook_p hook, char const *name)
{
	bt3c_softc_p	sc = (bt3c_softc_p) NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_BT3C_HOOK) != 0)
		return (EINVAL);

	if (sc->hook != NULL)
		return (EISCONN);

	sc->hook = hook;

	return (0);
}