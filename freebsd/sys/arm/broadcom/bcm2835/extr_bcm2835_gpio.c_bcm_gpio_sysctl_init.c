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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct bcm_gpio_sysctl {int /*<<< orphan*/  pin; struct bcm_gpio_softc* sc; } ;
struct bcm_gpio_softc {int sc_gpio_npins; TYPE_1__* sc_gpio_pins; struct bcm_gpio_sysctl* sc_sysctl; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  pinbuf ;
struct TYPE_2__ {int /*<<< orphan*/  gp_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct bcm_gpio_sysctl*,int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  bcm_gpio_func_proc ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
bcm_gpio_sysctl_init(struct bcm_gpio_softc *sc)
{
	char pinbuf[3];
	struct bcm_gpio_sysctl *sc_sysctl;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree_node, *pin_node, *pinN_node;
	struct sysctl_oid_list *tree, *pin_tree, *pinN_tree;
	int i;

	/*
	 * Add per-pin sysctl tree/handlers.
	 */
	ctx = device_get_sysctl_ctx(sc->sc_dev);
 	tree_node = device_get_sysctl_tree(sc->sc_dev);
 	tree = SYSCTL_CHILDREN(tree_node);
	pin_node = SYSCTL_ADD_NODE(ctx, tree, OID_AUTO, "pin",
	    CTLFLAG_RD, NULL, "GPIO Pins");
	pin_tree = SYSCTL_CHILDREN(pin_node);

	for (i = 0; i < sc->sc_gpio_npins; i++) {

		snprintf(pinbuf, sizeof(pinbuf), "%d", i);
		pinN_node = SYSCTL_ADD_NODE(ctx, pin_tree, OID_AUTO, pinbuf,
		    CTLFLAG_RD, NULL, "GPIO Pin");
		pinN_tree = SYSCTL_CHILDREN(pinN_node);

		sc->sc_sysctl[i].sc = sc;
		sc_sysctl = &sc->sc_sysctl[i];
		sc_sysctl->sc = sc;
		sc_sysctl->pin = sc->sc_gpio_pins[i].gp_pin;
		SYSCTL_ADD_PROC(ctx, pinN_tree, OID_AUTO, "function",
		    CTLFLAG_RW | CTLTYPE_STRING, sc_sysctl,
		    sizeof(struct bcm_gpio_sysctl), bcm_gpio_func_proc,
		    "A", "Pin Function");
	}
}