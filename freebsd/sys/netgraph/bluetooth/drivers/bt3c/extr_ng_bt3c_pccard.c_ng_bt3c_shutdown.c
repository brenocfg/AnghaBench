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
typedef  int /*<<< orphan*/ * node_p ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_3__ {int /*<<< orphan*/ * node; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ng_make_node_common (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typestruct ; 

__attribute__((used)) static int
ng_bt3c_shutdown(node_p node)
{
	bt3c_softc_p	sc = (bt3c_softc_p) NG_NODE_PRIVATE(node);

	/* Let old node go */
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);

	/* Create new fresh one if we are not going down */
	if (sc == NULL)
		goto out;

	/* Create new Netgraph node */
	if (ng_make_node_common(&typestruct, &sc->node) != 0) {
		device_printf(sc->dev, "Could not create Netgraph node\n");
		sc->node = NULL;
		goto out;
	}

	/* Name new Netgraph node */
	if (ng_name_node(sc->node,  device_get_nameunit(sc->dev)) != 0) {
		device_printf(sc->dev, "Could not name Netgraph node\n");
		NG_NODE_UNREF(sc->node);
		sc->node = NULL;
		goto out;
	}

	NG_NODE_SET_PRIVATE(sc->node, sc);
out:
	return (0);
}