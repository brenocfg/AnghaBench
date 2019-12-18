#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ctl_lo; int /*<<< orphan*/  ctl_hi; int /*<<< orphan*/  block_ts_lo; int /*<<< orphan*/  llp; int /*<<< orphan*/  dar; int /*<<< orphan*/  sar; } ;
struct axi_dma_desc {TYPE_2__ lli; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct axi_dma_chan {TYPE_1__ vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dchan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axi_chan_dump_lli(struct axi_dma_chan *chan,
			      struct axi_dma_desc *desc)
{
	dev_err(dchan2dev(&chan->vc.chan),
		"SAR: 0x%llx DAR: 0x%llx LLP: 0x%llx BTS 0x%x CTL: 0x%x:%08x",
		le64_to_cpu(desc->lli.sar),
		le64_to_cpu(desc->lli.dar),
		le64_to_cpu(desc->lli.llp),
		le32_to_cpu(desc->lli.block_ts_lo),
		le32_to_cpu(desc->lli.ctl_hi),
		le32_to_cpu(desc->lli.ctl_lo));
}