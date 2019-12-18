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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct nlm_xlpnae_softc {int nucores; TYPE_1__* portcfg; int /*<<< orphan*/ * cmplx_type; int /*<<< orphan*/  nblocks; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_desc_sizes; int /*<<< orphan*/  ucore_mask; int /*<<< orphan*/  vlan_pri_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGMIIC ; 
 int /*<<< orphan*/  XAUIC ; 
 int /*<<< orphan*/  nlm_config_egress (struct nlm_xlpnae_softc*,int,int,int,int) ; 
 int /*<<< orphan*/  nlm_config_freein_fifo_uniq_cfg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_config_ucore_iface_mask_cfg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_config_xaui (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_configure_sgmii_interface (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_nae_init_netior (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_nae_init_ucore (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nlm_nae_open_if (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_program_flow_cfg (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
nlm_setup_interface(struct nlm_xlpnae_softc *sc, int nblock,
    int port, uint32_t cur_flow_base, uint32_t flow_mask,
    int max_channels, int context)
{
	uint64_t nae_base = sc->base;
	int mtu = 1536;			/* XXXJC: don't hard code */
	uint32_t ucore_mask;

	if (sc->cmplx_type[nblock] == XAUIC)
		nlm_config_xaui(nae_base, nblock, mtu,
		    mtu, sc->portcfg[port].vlan_pri_en);
	nlm_config_freein_fifo_uniq_cfg(nae_base,
	    port, sc->portcfg[port].free_desc_sizes);
	nlm_config_ucore_iface_mask_cfg(nae_base,
	    port, sc->portcfg[port].ucore_mask);

	nlm_program_flow_cfg(nae_base, port, cur_flow_base, flow_mask);

	if (sc->cmplx_type[nblock] == SGMIIC)
		nlm_configure_sgmii_interface(nae_base, nblock, port, mtu, 0);

	nlm_config_egress(sc, nblock, context, port, max_channels);

	nlm_nae_init_netior(nae_base, sc->nblocks);
	nlm_nae_open_if(nae_base, nblock, sc->cmplx_type[nblock], port,
	    sc->portcfg[port].free_desc_sizes);

	/*  XXXJC: check mask calculation */
	ucore_mask = (1 << sc->nucores) - 1;
	nlm_nae_init_ucore(nae_base, port, ucore_mask);
}