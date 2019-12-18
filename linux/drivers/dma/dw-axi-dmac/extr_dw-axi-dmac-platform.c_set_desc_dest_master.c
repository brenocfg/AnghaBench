#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  ctl_lo; } ;
struct axi_dma_desc {TYPE_5__ lli; TYPE_4__* chan; } ;
struct TYPE_9__ {TYPE_3__* chip; } ;
struct TYPE_8__ {TYPE_2__* dw; } ;
struct TYPE_7__ {TYPE_1__* hdata; } ;
struct TYPE_6__ {int nr_masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_CTL_L_DST_MAST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_desc_dest_master(struct axi_dma_desc *desc)
{
	u32 val;

	/* Select AXI1 for source master if available */
	val = le32_to_cpu(desc->lli.ctl_lo);
	if (desc->chan->chip->dw->hdata->nr_masters > 1)
		val |= CH_CTL_L_DST_MAST;
	else
		val &= ~CH_CTL_L_DST_MAST;

	desc->lli.ctl_lo = cpu_to_le32(val);
}