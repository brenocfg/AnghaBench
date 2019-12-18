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
struct udbp_softc {char* sc_name; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_node; } ;
typedef  int /*<<< orphan*/ * node_p ;

/* Variables and functions */
 struct udbp_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ *,struct udbp_softc*) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ng_make_node_common (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ng_udbp_typestruct ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
ng_udbp_rmnode(node_p node)
{
	struct udbp_softc *sc = NG_NODE_PRIVATE(node);

	/* Let old node go */
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);		/* forget it ever existed */

	if (sc == NULL) {
		goto done;
	}
	/* Create Netgraph node */
	if (ng_make_node_common(&ng_udbp_typestruct, &sc->sc_node) != 0) {
		printf("%s: Could not create Netgraph node\n",
		    sc->sc_name);
		sc->sc_node = NULL;
		goto done;
	}
	/* Name node */
	if (ng_name_node(sc->sc_node, sc->sc_name) != 0) {
		printf("%s: Could not name Netgraph node\n",
		    sc->sc_name);
		NG_NODE_UNREF(sc->sc_node);
		sc->sc_node = NULL;
		goto done;
	}
	NG_NODE_SET_PRIVATE(sc->sc_node, sc);

done:
	if (sc) {
		mtx_unlock(&sc->sc_mtx);
	}
	return (0);
}