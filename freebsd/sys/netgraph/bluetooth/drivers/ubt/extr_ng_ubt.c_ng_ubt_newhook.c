#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ubt_softc {int /*<<< orphan*/ * sc_hook; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 struct ubt_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_UBT_HOOK ; 
 int /*<<< orphan*/  UBT_NG_LOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (struct ubt_softc*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ubt_newhook(node_p node, hook_p hook, char const *name)
{
	struct ubt_softc	*sc = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_UBT_HOOK) != 0)
		return (EINVAL);

	UBT_NG_LOCK(sc);
	if (sc->sc_hook != NULL) {
		UBT_NG_UNLOCK(sc);

		return (EISCONN);
	}

	sc->sc_hook = hook;
	UBT_NG_UNLOCK(sc);

	return (0);
}