#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  extio; } ;
struct TYPE_23__ {int /*<<< orphan*/  pbdma_dptr; int /*<<< orphan*/  pbdma_bptr; int /*<<< orphan*/  pbdma_ctrl; } ;
struct TYPE_22__ {unsigned long addr; int /*<<< orphan*/  ndptr; int /*<<< orphan*/  cbp; int /*<<< orphan*/  ctrl; } ;
struct TYPE_21__ {int /*<<< orphan*/  tx_ndptr; scalar_t__ tx_cbptr; int /*<<< orphan*/  tx_ctrl; int /*<<< orphan*/  rx_ndptr; scalar_t__ rx_cbptr; int /*<<< orphan*/  rx_ctrl; } ;
struct TYPE_20__ {unsigned long addr; int /*<<< orphan*/  ndptr; scalar_t__ cbp; int /*<<< orphan*/  ctrl; } ;
struct TYPE_19__ {unsigned long addr; int /*<<< orphan*/  ndptr; scalar_t__ cbp; int /*<<< orphan*/  ctrl; } ;
struct TYPE_18__ {int /*<<< orphan*/  ndptr; int /*<<< orphan*/  cbptr; int /*<<< orphan*/  ctrl; } ;
struct TYPE_17__ {unsigned long addr; int /*<<< orphan*/  ndptr; int /*<<< orphan*/  cbp; int /*<<< orphan*/  ctrl; } ;
struct TYPE_16__ {int /*<<< orphan*/  ndptr; int /*<<< orphan*/  cbptr; int /*<<< orphan*/  ctrl; } ;
struct TYPE_15__ {TYPE_7__* pbdma; TYPE_5__ ethtx; TYPE_4__ ethrx; TYPE_2__* scsi; } ;
struct TYPE_14__ {TYPE_8__* pbdma; TYPE_6__ ethregs; TYPE_3__ scsi_chan1; TYPE_1__ scsi_chan0; int /*<<< orphan*/  bestat; } ;
struct TYPE_13__ {int cerr; int cstat; int gerr; int gstat; } ;

/* Variables and functions */
 int CPU_ERRMASK ; 
 int cpu_err_addr ; 
 int cpu_err_stat ; 
 int /*<<< orphan*/  extio_stat ; 
 int gio_err_addr ; 
 int gio_err_stat ; 
 TYPE_12__ hpc3 ; 
 int /*<<< orphan*/  hpc3_berr_stat ; 
 TYPE_11__* hpc3c0 ; 
 int /*<<< orphan*/  save_cache_tags (int) ; 
 TYPE_10__* sgimc ; 
 TYPE_9__* sgioc ; 

__attribute__((used)) static void save_and_clear_buserr(void)
{
	int i;

	/* save status registers */
	cpu_err_addr = sgimc->cerr;
	cpu_err_stat = sgimc->cstat;
	gio_err_addr = sgimc->gerr;
	gio_err_stat = sgimc->gstat;
	extio_stat = sgioc->extio;
	hpc3_berr_stat = hpc3c0->bestat;

	hpc3.scsi[0].addr  = (unsigned long)&hpc3c0->scsi_chan0;
	hpc3.scsi[0].ctrl  = hpc3c0->scsi_chan0.ctrl; /* HPC3_SCTRL_ACTIVE ? */
	hpc3.scsi[0].cbp   = hpc3c0->scsi_chan0.cbptr;
	hpc3.scsi[0].ndptr = hpc3c0->scsi_chan0.ndptr;

	hpc3.scsi[1].addr  = (unsigned long)&hpc3c0->scsi_chan1;
	hpc3.scsi[1].ctrl  = hpc3c0->scsi_chan1.ctrl; /* HPC3_SCTRL_ACTIVE ? */
	hpc3.scsi[1].cbp   = hpc3c0->scsi_chan1.cbptr;
	hpc3.scsi[1].ndptr = hpc3c0->scsi_chan1.ndptr;

	hpc3.ethrx.addr	 = (unsigned long)&hpc3c0->ethregs.rx_cbptr;
	hpc3.ethrx.ctrl	 = hpc3c0->ethregs.rx_ctrl; /* HPC3_ERXCTRL_ACTIVE ? */
	hpc3.ethrx.cbp	 = hpc3c0->ethregs.rx_cbptr;
	hpc3.ethrx.ndptr = hpc3c0->ethregs.rx_ndptr;

	hpc3.ethtx.addr	 = (unsigned long)&hpc3c0->ethregs.tx_cbptr;
	hpc3.ethtx.ctrl	 = hpc3c0->ethregs.tx_ctrl; /* HPC3_ETXCTRL_ACTIVE ? */
	hpc3.ethtx.cbp	 = hpc3c0->ethregs.tx_cbptr;
	hpc3.ethtx.ndptr = hpc3c0->ethregs.tx_ndptr;

	for (i = 0; i < 8; ++i) {
		/* HPC3_PDMACTRL_ISACT ? */
		hpc3.pbdma[i].addr  = (unsigned long)&hpc3c0->pbdma[i];
		hpc3.pbdma[i].ctrl  = hpc3c0->pbdma[i].pbdma_ctrl;
		hpc3.pbdma[i].cbp   = hpc3c0->pbdma[i].pbdma_bptr;
		hpc3.pbdma[i].ndptr = hpc3c0->pbdma[i].pbdma_dptr;
	}
	i = 0;
	if (gio_err_stat & CPU_ERRMASK)
		i = gio_err_addr;
	if (cpu_err_stat & CPU_ERRMASK)
		i = cpu_err_addr;
	save_cache_tags(i);

	sgimc->cstat = sgimc->gstat = 0;
}