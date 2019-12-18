#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_23__ {int apctl_v_agp_rate; int /*<<< orphan*/  apctl_v_agp_en; int /*<<< orphan*/  apctl_v_agp_sba_en; } ;
union TPAchipPCTL {TYPE_7__ pctl_r_bits; int /*<<< orphan*/  pctl_q_whole; } ;
struct TYPE_20__ {int /*<<< orphan*/  csr; } ;
struct TYPE_24__ {TYPE_4__ pctl; } ;
typedef  TYPE_8__ titan_pachip_port ;
struct pci_controller {int index; int /*<<< orphan*/  sg_pci; struct pci_controller* next; } ;
struct TYPE_21__ {int rate; int rq; int /*<<< orphan*/  enable; int /*<<< orphan*/  sba; } ;
struct TYPE_22__ {TYPE_5__ bits; scalar_t__ lw; } ;
struct TYPE_18__ {int rate; int sba; int rq; } ;
struct TYPE_19__ {TYPE_2__ bits; scalar_t__ lw; } ;
struct TYPE_17__ {int /*<<< orphan*/ * sysdata; scalar_t__ size; scalar_t__ bus_base; } ;
struct TYPE_25__ {TYPE_6__ mode; TYPE_3__ capability; TYPE_1__ aperture; int /*<<< orphan*/ * ops; TYPE_8__* private; struct pci_controller* hose; } ;
typedef  TYPE_9__ alpha_agp_info ;
struct TYPE_16__ {TYPE_8__ a_port; } ;
struct TYPE_15__ {TYPE_8__ a_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_14__* TITAN_pachip0 ; 
 TYPE_13__* TITAN_pachip1 ; 
 struct pci_controller* hose_head ; 
 TYPE_9__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  titan_agp_ops ; 
 scalar_t__ titan_pchip1_present ; 
 scalar_t__ titan_query_agp (TYPE_8__*) ; 

alpha_agp_info *
titan_agp_info(void)
{
	alpha_agp_info *agp;
	struct pci_controller *hose;
	titan_pachip_port *port;
	int hosenum = -1;
	union TPAchipPCTL pctl;

	/*
	 * Find the AGP port.
	 */
	port = &TITAN_pachip0->a_port;
	if (titan_query_agp(port))
		hosenum = 2;
	if (hosenum < 0 && 
	    titan_pchip1_present &&
	    titan_query_agp(port = &TITAN_pachip1->a_port)) 
		hosenum = 3;
	
	/*
	 * Find the hose the port is on.
	 */
	for (hose = hose_head; hose; hose = hose->next)
		if (hose->index == hosenum)
			break;

	if (!hose || !hose->sg_pci)
		return NULL;

	/*
	 * Allocate the info structure.
	 */
	agp = kmalloc(sizeof(*agp), GFP_KERNEL);
	if (!agp)
		return NULL;

	/*
	 * Fill it in.
	 */
	agp->hose = hose;
	agp->private = port;
	agp->ops = &titan_agp_ops;

	/*
	 * Aperture - not configured until ops.setup().
	 *
	 * FIXME - should we go ahead and allocate it here?
	 */
	agp->aperture.bus_base = 0;
	agp->aperture.size = 0;
	agp->aperture.sysdata = NULL;

	/*
	 * Capabilities.
	 */
	agp->capability.lw = 0;
	agp->capability.bits.rate = 3; 	/* 2x, 1x */
	agp->capability.bits.sba = 1;
	agp->capability.bits.rq = 7;	/* 8 - 1 */

	/*
	 * Mode.
	 */
	pctl.pctl_q_whole = port->pctl.csr;
	agp->mode.lw = 0;
	agp->mode.bits.rate = 1 << pctl.pctl_r_bits.apctl_v_agp_rate;
	agp->mode.bits.sba = pctl.pctl_r_bits.apctl_v_agp_sba_en;
	agp->mode.bits.rq = 7;	/* RQ Depth? */
	agp->mode.bits.enable = pctl.pctl_r_bits.apctl_v_agp_en;

	return agp;
}