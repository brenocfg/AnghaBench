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
typedef  int uint32_t ;
struct nlm_xlpnae_softc {scalar_t__* cmplx_type; int /*<<< orphan*/  base; TYPE_1__* portcfg; } ;
struct TYPE_3__ {int num_channels; } ;

/* Variables and functions */
 scalar_t__ ILC ; 
 int /*<<< orphan*/  NAE_DMA_TX_CREDIT_TH ; 
 int NAE_DRR_QUANTA ; 
 int /*<<< orphan*/  NAE_TX_DDR_ACTVLIST_CMD ; 
 int /*<<< orphan*/  NAE_TX_IF_BURSTMAX_CMD ; 
 int /*<<< orphan*/  NAE_TX_SCHED_MAP_CMD0 ; 
 int /*<<< orphan*/  NAE_TX_SCHED_MAP_CMD1 ; 
 int /*<<< orphan*/  config_egress_fifo_carvings (int /*<<< orphan*/ ,int,int,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  config_egress_fifo_credits (int /*<<< orphan*/ ,int,int,int,int,TYPE_1__*) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nlm_config_egress(struct nlm_xlpnae_softc *sc, int nblock,
    int context_base, int hwport, int max_channels)
{
	int offset, num_channels;
	uint32_t data;

	num_channels = sc->portcfg[hwport].num_channels;

	data = (2048 << 12) | (hwport << 4) | 1;
	nlm_write_nae_reg(sc->base, NAE_TX_IF_BURSTMAX_CMD, data);

	data = ((context_base + num_channels - 1) << 22) |
	    (context_base << 12) | (hwport << 4) | 1;
	nlm_write_nae_reg(sc->base, NAE_TX_DDR_ACTVLIST_CMD, data);

	config_egress_fifo_carvings(sc->base, hwport,
	    context_base, num_channels, max_channels, sc->portcfg);
	config_egress_fifo_credits(sc->base, hwport,
	    context_base, num_channels, max_channels, sc->portcfg);

	data = nlm_read_nae_reg(sc->base, NAE_DMA_TX_CREDIT_TH);
	data |= (1 << 25) | (1 << 24);
	nlm_write_nae_reg(sc->base, NAE_DMA_TX_CREDIT_TH, data);

	for (offset = 0; offset < num_channels; offset++) {
		nlm_write_nae_reg(sc->base, NAE_TX_SCHED_MAP_CMD1,
		    NAE_DRR_QUANTA);
		data = (hwport << 15) | ((context_base + offset) << 5);
		if (sc->cmplx_type[nblock] == ILC)
			data |= (offset << 20);
		nlm_write_nae_reg(sc->base, NAE_TX_SCHED_MAP_CMD0, data | 1);
		nlm_write_nae_reg(sc->base, NAE_TX_SCHED_MAP_CMD0, data);
	}
}