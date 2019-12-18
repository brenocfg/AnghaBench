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
typedef  int u8 ;
struct ixgbe_dcb_tc_path {int bwg_percent; int bwg_id; scalar_t__ tsa; } ;
struct ixgbe_dcb_config {int** bw_percentage; TYPE_1__* tc_config; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  link_strict ;
typedef  int /*<<< orphan*/  bw_sum ;
struct TYPE_2__ {struct ixgbe_dcb_tc_path* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT2 (char*,int /*<<< orphan*/ ,char*) ; 
 int IXGBE_DCB_BW_PERCENT ; 
 int IXGBE_DCB_MAX_BW_GROUP ; 
 int IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int IXGBE_DCB_TX_CONFIG ; 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int TRUE ; 
 scalar_t__ ixgbe_dcb_tsa_strict ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

s32 ixgbe_dcb_check_config_cee(struct ixgbe_dcb_config *dcb_config)
{
	struct ixgbe_dcb_tc_path *p;
	s32 ret_val = IXGBE_SUCCESS;
	u8 i, j, bw = 0, bw_id;
	u8 bw_sum[2][IXGBE_DCB_MAX_BW_GROUP];
	bool link_strict[2][IXGBE_DCB_MAX_BW_GROUP];

	memset(bw_sum, 0, sizeof(bw_sum));
	memset(link_strict, 0, sizeof(link_strict));

	/* First Tx, then Rx */
	for (i = 0; i < 2; i++) {
		/* Check each traffic class for rule violation */
		for (j = 0; j < IXGBE_DCB_MAX_TRAFFIC_CLASS; j++) {
			p = &dcb_config->tc_config[j].path[i];

			bw = p->bwg_percent;
			bw_id = p->bwg_id;

			if (bw_id >= IXGBE_DCB_MAX_BW_GROUP) {
				ret_val = IXGBE_ERR_CONFIG;
				goto err_config;
			}
			if (p->tsa == ixgbe_dcb_tsa_strict) {
				link_strict[i][bw_id] = TRUE;
				/* Link strict should have zero bandwidth */
				if (bw) {
					ret_val = IXGBE_ERR_CONFIG;
					goto err_config;
				}
			} else if (!bw) {
				/*
				 * Traffic classes without link strict
				 * should have non-zero bandwidth.
				 */
				ret_val = IXGBE_ERR_CONFIG;
				goto err_config;
			}
			bw_sum[i][bw_id] += bw;
		}

		bw = 0;

		/* Check each bandwidth group for rule violation */
		for (j = 0; j < IXGBE_DCB_MAX_BW_GROUP; j++) {
			bw += dcb_config->bw_percentage[i][j];
			/*
			 * Sum of bandwidth percentages of all traffic classes
			 * within a Bandwidth Group must total 100 except for
			 * link strict group (zero bandwidth).
			 */
			if (link_strict[i][j]) {
				if (bw_sum[i][j]) {
					/*
					 * Link strict group should have zero
					 * bandwidth.
					 */
					ret_val = IXGBE_ERR_CONFIG;
					goto err_config;
				}
			} else if (bw_sum[i][j] != IXGBE_DCB_BW_PERCENT &&
				   bw_sum[i][j] != 0) {
				ret_val = IXGBE_ERR_CONFIG;
				goto err_config;
			}
		}

		if (bw != IXGBE_DCB_BW_PERCENT) {
			ret_val = IXGBE_ERR_CONFIG;
			goto err_config;
		}
	}

err_config:
	DEBUGOUT2("DCB error code %d while checking %s settings.\n",
		  ret_val, (i == IXGBE_DCB_TX_CONFIG) ? "Tx" : "Rx");

	return ret_val;
}