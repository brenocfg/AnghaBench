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
struct udbp_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_hook; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct udbp_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_UDBP_HOOK_NAME ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_udbp_newhook(node_p node, hook_p hook, const char *name)
{
	struct udbp_softc *sc = NG_NODE_PRIVATE(node);
	int32_t error = 0;

	if (strcmp(name, NG_UDBP_HOOK_NAME)) {
		return (EINVAL);
	}
	mtx_lock(&sc->sc_mtx);

	if (sc->sc_hook != NULL) {
		error = EISCONN;
	} else {
		sc->sc_hook = hook;
		NG_HOOK_SET_PRIVATE(hook, NULL);
	}

	mtx_unlock(&sc->sc_mtx);

	return (error);
}