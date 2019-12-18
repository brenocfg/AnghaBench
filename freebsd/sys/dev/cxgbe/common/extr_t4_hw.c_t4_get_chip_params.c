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
struct chip_params {int cng_ch_bits_log; int nsched_cls; int mps_rplc_size; int vfcount; int sge_fl_db; int /*<<< orphan*/  const mps_tcam_size; int /*<<< orphan*/  const cim_num_obq; int /*<<< orphan*/  const pm_stats_cnt; int /*<<< orphan*/  const nchan; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct chip_params const*) ; 
 scalar_t__ CHELSIO_T4 ; 
#define  CIM_NUM_OBQ 137 
#define  CIM_NUM_OBQ_T5 136 
#define  F_DBPRIO 135 
#define  F_DBTYPE 134 
#define  NCHAN 133 
#define  NUM_MPS_CLS_SRAM_L_INSTANCES 132 
#define  NUM_MPS_T5_CLS_SRAM_L_INSTANCES 131 
#define  PM_NSTATS 130 
#define  T6_NCHAN 129 
#define  T6_PM_NSTATS 128 

const struct chip_params *t4_get_chip_params(int chipid)
{
	static const struct chip_params chip_params[] = {
		{
			/* T4 */
			.nchan = NCHAN,
			.pm_stats_cnt = PM_NSTATS,
			.cng_ch_bits_log = 2,
			.nsched_cls = 15,
			.cim_num_obq = CIM_NUM_OBQ,
			.mps_rplc_size = 128,
			.vfcount = 128,
			.sge_fl_db = F_DBPRIO,
			.mps_tcam_size = NUM_MPS_CLS_SRAM_L_INSTANCES,
		},
		{
			/* T5 */
			.nchan = NCHAN,
			.pm_stats_cnt = PM_NSTATS,
			.cng_ch_bits_log = 2,
			.nsched_cls = 16,
			.cim_num_obq = CIM_NUM_OBQ_T5,
			.mps_rplc_size = 128,
			.vfcount = 128,
			.sge_fl_db = F_DBPRIO | F_DBTYPE,
			.mps_tcam_size = NUM_MPS_T5_CLS_SRAM_L_INSTANCES,
		},
		{
			/* T6 */
			.nchan = T6_NCHAN,
			.pm_stats_cnt = T6_PM_NSTATS,
			.cng_ch_bits_log = 3,
			.nsched_cls = 16,
			.cim_num_obq = CIM_NUM_OBQ_T5,
			.mps_rplc_size = 256,
			.vfcount = 256,
			.sge_fl_db = 0,
			.mps_tcam_size = NUM_MPS_T5_CLS_SRAM_L_INSTANCES,
		},
	};

	chipid -= CHELSIO_T4;
	if (chipid < 0 || chipid >= ARRAY_SIZE(chip_params))
		return NULL;

	return &chip_params[chipid];
}