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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct mv88e61xxphy_softc {struct mv88e61xxphy_port_softc* sc_ports; int /*<<< orphan*/  sc_dev; } ;
struct mv88e61xxphy_port_softc {unsigned int sc_port; unsigned int sc_vlan; scalar_t__ sc_flags; scalar_t__ sc_priority; scalar_t__ sc_domain; struct mv88e61xxphy_softc* sc_switch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  MV88E61XXPHY_LINK_SYSCTL_DUPLEX ; 
 int /*<<< orphan*/  MV88E61XXPHY_LINK_SYSCTL_LINK ; 
 int /*<<< orphan*/  MV88E61XXPHY_LINK_SYSCTL_MEDIA ; 
 int /*<<< orphan*/  MV88E61XXPHY_PORT_SYSCTL_DOMAIN ; 
 int /*<<< orphan*/  MV88E61XXPHY_PORT_SYSCTL_PRIORITY ; 
 int /*<<< orphan*/  MV88E61XXPHY_PORT_SYSCTL_VLAN ; 
 unsigned int MV88E61XX_PORTS ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct mv88e61xxphy_port_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct mv88e61xxphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e61xxphy_init (struct mv88e61xxphy_softc*) ; 
 int /*<<< orphan*/  mv88e61xxphy_sysctl_link_proc ; 
 int /*<<< orphan*/  mv88e61xxphy_sysctl_port_proc ; 

__attribute__((used)) static int
mv88e61xxphy_attach(device_t dev)
{
	char portbuf[] = "N";
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(dev);
	struct sysctl_oid_list *child = SYSCTL_CHILDREN(tree);
	struct sysctl_oid *port_node, *portN_node;
	struct sysctl_oid_list *port_tree, *portN_tree;
	struct mv88e61xxphy_softc *sc;
	unsigned port;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	/*
	 * Initialize port softcs.
	 */
	for (port = 0; port < MV88E61XX_PORTS; port++) {
		struct mv88e61xxphy_port_softc *psc;

		psc = &sc->sc_ports[port];
		psc->sc_switch = sc;
		psc->sc_port = port;
		psc->sc_domain = 0; /* One broadcast domain by default.  */
		psc->sc_vlan = port + 1; /* Tag VLANs by default.  */
		psc->sc_priority = 0; /* No default special priority.  */
		psc->sc_flags = 0;
	}

	/*
	 * Add per-port sysctl tree/handlers.
	 */
	port_node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "port",
	    CTLFLAG_RD, NULL, "Switch Ports");
	port_tree = SYSCTL_CHILDREN(port_node);
	for (port = 0; port < MV88E61XX_PORTS; port++) {
		struct mv88e61xxphy_port_softc *psc;

		psc = &sc->sc_ports[port];

		portbuf[0] = '0' + port;
		portN_node = SYSCTL_ADD_NODE(ctx, port_tree, OID_AUTO, portbuf,
		    CTLFLAG_RD, NULL, "Switch Port");
		portN_tree = SYSCTL_CHILDREN(portN_node);

		SYSCTL_ADD_PROC(ctx, portN_tree, OID_AUTO, "duplex",
		    CTLFLAG_RD | CTLTYPE_INT, psc,
		    MV88E61XXPHY_LINK_SYSCTL_DUPLEX,
		    mv88e61xxphy_sysctl_link_proc, "IU",
		    "Media duplex status (0 = half duplex; 1 = full duplex)");

		SYSCTL_ADD_PROC(ctx, portN_tree, OID_AUTO, "link",
		    CTLFLAG_RD | CTLTYPE_INT, psc,
		    MV88E61XXPHY_LINK_SYSCTL_LINK,
		    mv88e61xxphy_sysctl_link_proc, "IU",
		    "Link status (0 = down; 1 = up)");

		SYSCTL_ADD_PROC(ctx, portN_tree, OID_AUTO, "media",
		    CTLFLAG_RD | CTLTYPE_INT, psc,
		    MV88E61XXPHY_LINK_SYSCTL_MEDIA,
		    mv88e61xxphy_sysctl_link_proc, "IU",
		    "Media speed (0 = unknown; 10 = 10Mbps; 100 = 100Mbps; 1000 = 1Gbps)");

		SYSCTL_ADD_PROC(ctx, portN_tree, OID_AUTO, "domain",
		    CTLFLAG_RW | CTLTYPE_INT, psc,
		    MV88E61XXPHY_PORT_SYSCTL_DOMAIN,
		    mv88e61xxphy_sysctl_port_proc, "IU",
		    "Broadcast domain (ports can only talk to other ports in the same domain)");

		SYSCTL_ADD_PROC(ctx, portN_tree, OID_AUTO, "vlan",
		    CTLFLAG_RW | CTLTYPE_INT, psc,
		    MV88E61XXPHY_PORT_SYSCTL_VLAN,
		    mv88e61xxphy_sysctl_port_proc, "IU",
		    "Tag packets from/for this port with a given VLAN.");

		SYSCTL_ADD_PROC(ctx, portN_tree, OID_AUTO, "priority",
		    CTLFLAG_RW | CTLTYPE_INT, psc,
		    MV88E61XXPHY_PORT_SYSCTL_PRIORITY,
		    mv88e61xxphy_sysctl_port_proc, "IU",
		    "Default packet priority for this port.");
	}

	mv88e61xxphy_init(sc);

	return (0);
}