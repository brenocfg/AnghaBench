#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct debugfs_entries {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_12__ {scalar_t__ mode; int rd_ch_cnt; } ;
struct TYPE_11__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;
struct TYPE_8__ {TYPE_1__* ch; } ;
struct TYPE_9__ {TYPE_2__ unroll; } ;
struct TYPE_10__ {TYPE_3__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/ * padding_2; int /*<<< orphan*/  rd; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct debugfs_entries const*) ; 
 char* CHANNEL_STR ; 
 scalar_t__ EDMA_MODE_UNROLL ; 
 struct debugfs_entries const RD_REGISTER (int /*<<< orphan*/ ) ; 
 struct debugfs_entries const RD_REGISTER_UNROLL (int /*<<< orphan*/ ) ; 
 char* READ_STR ; 
 int /*<<< orphan*/  abort_imwr_high ; 
 int /*<<< orphan*/  abort_imwr_low ; 
 int /*<<< orphan*/  ch01_imwr_data ; 
 int /*<<< orphan*/  ch0_pwr_en ; 
 int /*<<< orphan*/  ch1_pwr_en ; 
 int /*<<< orphan*/  ch23_imwr_data ; 
 int /*<<< orphan*/  ch2_pwr_en ; 
 int /*<<< orphan*/  ch3_pwr_en ; 
 int /*<<< orphan*/  ch45_imwr_data ; 
 int /*<<< orphan*/  ch4_pwr_en ; 
 int /*<<< orphan*/  ch5_pwr_en ; 
 int /*<<< orphan*/  ch67_imwr_data ; 
 int /*<<< orphan*/  ch6_pwr_en ; 
 int /*<<< orphan*/  ch7_pwr_en ; 
 int /*<<< orphan*/  ch_arb_weight_high ; 
 int /*<<< orphan*/  ch_arb_weight_low ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  done_imwr_high ; 
 int /*<<< orphan*/  done_imwr_low ; 
 int /*<<< orphan*/  doorbell ; 
 TYPE_6__* dw ; 
 int /*<<< orphan*/  dw_edma_debugfs_create_x32 (struct debugfs_entries const*,int,struct dentry*) ; 
 int /*<<< orphan*/  dw_edma_debugfs_regs_ch (int /*<<< orphan*/ *,struct dentry*) ; 
 int /*<<< orphan*/  engine_chgroup ; 
 int /*<<< orphan*/  engine_en ; 
 int /*<<< orphan*/  engine_hshake_cnt_high ; 
 int /*<<< orphan*/  engine_hshake_cnt_low ; 
 int /*<<< orphan*/  err_status_high ; 
 int /*<<< orphan*/  err_status_low ; 
 int /*<<< orphan*/  int_clear ; 
 int /*<<< orphan*/  int_mask ; 
 int /*<<< orphan*/  int_status ; 
 TYPE_5__** lim ; 
 int /*<<< orphan*/  linked_list_err_en ; 
 TYPE_4__* regs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void dw_edma_debugfs_regs_rd(struct dentry *dir)
{
	const struct debugfs_entries debugfs_regs[] = {
		/* eDMA global registers */
		RD_REGISTER(engine_en),
		RD_REGISTER(doorbell),
		RD_REGISTER(ch_arb_weight_low),
		RD_REGISTER(ch_arb_weight_high),
		/* eDMA interrupts registers */
		RD_REGISTER(int_status),
		RD_REGISTER(int_mask),
		RD_REGISTER(int_clear),
		RD_REGISTER(err_status_low),
		RD_REGISTER(err_status_high),
		RD_REGISTER(linked_list_err_en),
		RD_REGISTER(done_imwr_low),
		RD_REGISTER(done_imwr_high),
		RD_REGISTER(abort_imwr_low),
		RD_REGISTER(abort_imwr_high),
		RD_REGISTER(ch01_imwr_data),
		RD_REGISTER(ch23_imwr_data),
		RD_REGISTER(ch45_imwr_data),
		RD_REGISTER(ch67_imwr_data),
	};
	const struct debugfs_entries debugfs_unroll_regs[] = {
		/* eDMA channel context grouping */
		RD_REGISTER_UNROLL(engine_chgroup),
		RD_REGISTER_UNROLL(engine_hshake_cnt_low),
		RD_REGISTER_UNROLL(engine_hshake_cnt_high),
		RD_REGISTER_UNROLL(ch0_pwr_en),
		RD_REGISTER_UNROLL(ch1_pwr_en),
		RD_REGISTER_UNROLL(ch2_pwr_en),
		RD_REGISTER_UNROLL(ch3_pwr_en),
		RD_REGISTER_UNROLL(ch4_pwr_en),
		RD_REGISTER_UNROLL(ch5_pwr_en),
		RD_REGISTER_UNROLL(ch6_pwr_en),
		RD_REGISTER_UNROLL(ch7_pwr_en),
	};
	struct dentry *regs_dir, *ch_dir;
	int nr_entries, i;
	char name[16];

	regs_dir = debugfs_create_dir(READ_STR, dir);
	if (!regs_dir)
		return;

	nr_entries = ARRAY_SIZE(debugfs_regs);
	dw_edma_debugfs_create_x32(debugfs_regs, nr_entries, regs_dir);

	if (dw->mode == EDMA_MODE_UNROLL) {
		nr_entries = ARRAY_SIZE(debugfs_unroll_regs);
		dw_edma_debugfs_create_x32(debugfs_unroll_regs, nr_entries,
					   regs_dir);
	}

	for (i = 0; i < dw->rd_ch_cnt; i++) {
		snprintf(name, sizeof(name), "%s:%d", CHANNEL_STR, i);

		ch_dir = debugfs_create_dir(name, regs_dir);
		if (!ch_dir)
			return;

		dw_edma_debugfs_regs_ch(&regs->type.unroll.ch[i].rd, ch_dir);

		lim[1][i].start = &regs->type.unroll.ch[i].rd;
		lim[1][i].end = &regs->type.unroll.ch[i].padding_2[0];
	}
}