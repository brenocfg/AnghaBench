#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xlp_port_ivars {int block; int port; scalar_t__ hw_parser_en; int /*<<< orphan*/  mdio_bus; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  type; int /*<<< orphan*/  node; } ;
struct nlm_xlpge_softc {int block; int port; int /*<<< orphan*/  base_addr; scalar_t__ hw_parser_en; int /*<<< orphan*/  nfree_desc; int /*<<< orphan*/  rxfreeq; int /*<<< orphan*/  txq; int /*<<< orphan*/  xlpge_callout; TYPE_1__* network_sc; int /*<<< orphan*/  prepad_size; int /*<<< orphan*/  prepad_en; int /*<<< orphan*/  flowctrl; int /*<<< orphan*/  link; int /*<<< orphan*/  duplexity; int /*<<< orphan*/  speed; TYPE_2__* portcfg; int /*<<< orphan*/  mdio_bus; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/ * xlpge_if; int /*<<< orphan*/  type; int /*<<< orphan*/  node; int /*<<< orphan*/ * mii_bus; int /*<<< orphan*/  xlpge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {struct nlm_xlpge_softc* xlpge_sc; } ;
struct TYPE_5__ {int /*<<< orphan*/  rxfreeq; int /*<<< orphan*/  txq; int /*<<< orphan*/  num_free_descs; } ;
struct TYPE_4__ {int /*<<< orphan*/  prepad_size; int /*<<< orphan*/  prepad_en; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_FLOWCTRL_DISABLED ; 
 int /*<<< orphan*/  NLM_LINK_DOWN ; 
 int /*<<< orphan*/  NLM_SGMII_DUPLEX_FULL ; 
 int /*<<< orphan*/  NLM_SGMII_SPEED_10 ; 
 int /*<<< orphan*/  XLPGE_LOCK_INIT (struct nlm_xlpge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 struct xlp_port_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_3__* ifp_ports ; 
 TYPE_2__* nae_port_config ; 
 int /*<<< orphan*/  nlm_enable_hardware_parser_per_port (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nlm_xlpge_ifinit (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_mii_init (int /*<<< orphan*/ ,struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_setup_stats_sysctl (int /*<<< orphan*/ ,struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_submit_rx_free_desc (struct nlm_xlpge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nlm_xlpge_attach(device_t dev)
{
	struct xlp_port_ivars *pv;
	struct nlm_xlpge_softc *sc;
	int port;

	pv = device_get_ivars(dev);
	sc = device_get_softc(dev);
	sc->xlpge_dev = dev;
	sc->mii_bus = NULL;
	sc->block = pv->block;
	sc->node = pv->node;
	sc->port = pv->port;
	sc->type = pv->type;
	sc->xlpge_if = NULL;
	sc->phy_addr = pv->phy_addr;
	sc->mdio_bus = pv->mdio_bus;
	sc->portcfg = nae_port_config;
	sc->hw_parser_en = pv->hw_parser_en;

	/* default settings */
	sc->speed = NLM_SGMII_SPEED_10;
	sc->duplexity = NLM_SGMII_DUPLEX_FULL;
	sc->link = NLM_LINK_DOWN;
	sc->flowctrl = NLM_FLOWCTRL_DISABLED;

	sc->network_sc = device_get_softc(device_get_parent(dev));
	sc->base_addr = sc->network_sc->base;
	sc->prepad_en = sc->network_sc->prepad_en;
	sc->prepad_size = sc->network_sc->prepad_size;

	callout_init(&sc->xlpge_callout, 1);

	XLPGE_LOCK_INIT(sc, device_get_nameunit(dev));

	port = (sc->block*4)+sc->port;
	sc->nfree_desc = nae_port_config[port].num_free_descs;
	sc->txq = nae_port_config[port].txq;
	sc->rxfreeq = nae_port_config[port].rxfreeq;

	nlm_xlpge_submit_rx_free_desc(sc, sc->nfree_desc);
	if (sc->hw_parser_en)
		nlm_enable_hardware_parser_per_port(sc->base_addr,
		    sc->block, sc->port);

	nlm_xlpge_ifinit(sc);
	ifp_ports[port].xlpge_sc = sc;
	nlm_xlpge_mii_init(dev, sc);

	nlm_xlpge_setup_stats_sysctl(dev, sc);

	return (0);
}