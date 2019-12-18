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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_dcb_tc_path {size_t bwg_id; size_t bwg_percent; size_t link_percent; size_t data_credits_refill; size_t data_credits_max; } ;
struct ixgbe_dcb_config {size_t** bw_percentage; TYPE_2__* tc_config; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {size_t desc_credits_max; struct ixgbe_dcb_tc_path* path; } ;

/* Variables and functions */
 int IXGBE_DCB_CREDIT_QUANTUM ; 
 size_t IXGBE_DCB_MAX_CREDIT ; 
 scalar_t__ IXGBE_DCB_MAX_CREDIT_REFILL ; 
 size_t IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int IXGBE_DCB_MIN_TSO_CREDIT ; 
 size_t IXGBE_DCB_TX_CONFIG ; 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int min (size_t,int) ; 

s32 ixgbe_dcb_calculate_tc_credits_cee(struct ixgbe_hw *hw,
				   struct ixgbe_dcb_config *dcb_config,
				   u32 max_frame_size, u8 direction)
{
	struct ixgbe_dcb_tc_path *p;
	u32 min_multiplier	= 0;
	u16 min_percent		= 100;
	s32 ret_val =		IXGBE_SUCCESS;
	/* Initialization values default for Tx settings */
	u32 min_credit		= 0;
	u32 credit_refill	= 0;
	u32 credit_max		= 0;
	u16 link_percentage	= 0;
	u8  bw_percent		= 0;
	u8  i;

	if (dcb_config == NULL) {
		ret_val = IXGBE_ERR_CONFIG;
		goto out;
	}

	min_credit = ((max_frame_size / 2) + IXGBE_DCB_CREDIT_QUANTUM - 1) /
		     IXGBE_DCB_CREDIT_QUANTUM;

	/* Find smallest link percentage */
	for (i = 0; i < IXGBE_DCB_MAX_TRAFFIC_CLASS; i++) {
		p = &dcb_config->tc_config[i].path[direction];
		bw_percent = dcb_config->bw_percentage[direction][p->bwg_id];
		link_percentage = p->bwg_percent;

		link_percentage = (link_percentage * bw_percent) / 100;

		if (link_percentage && link_percentage < min_percent)
			min_percent = link_percentage;
	}

	/*
	 * The ratio between traffic classes will control the bandwidth
	 * percentages seen on the wire. To calculate this ratio we use
	 * a multiplier. It is required that the refill credits must be
	 * larger than the max frame size so here we find the smallest
	 * multiplier that will allow all bandwidth percentages to be
	 * greater than the max frame size.
	 */
	min_multiplier = (min_credit / min_percent) + 1;

	/* Find out the link percentage for each TC first */
	for (i = 0; i < IXGBE_DCB_MAX_TRAFFIC_CLASS; i++) {
		p = &dcb_config->tc_config[i].path[direction];
		bw_percent = dcb_config->bw_percentage[direction][p->bwg_id];

		link_percentage = p->bwg_percent;
		/* Must be careful of integer division for very small nums */
		link_percentage = (link_percentage * bw_percent) / 100;
		if (p->bwg_percent > 0 && link_percentage == 0)
			link_percentage = 1;

		/* Save link_percentage for reference */
		p->link_percent = (u8)link_percentage;

		/* Calculate credit refill ratio using multiplier */
		credit_refill = min(link_percentage * min_multiplier,
				    (u32)IXGBE_DCB_MAX_CREDIT_REFILL);

		/* Refill at least minimum credit */
		if (credit_refill < min_credit)
			credit_refill = min_credit;

		p->data_credits_refill = (u16)credit_refill;

		/* Calculate maximum credit for the TC */
		credit_max = (link_percentage * IXGBE_DCB_MAX_CREDIT) / 100;

		/*
		 * Adjustment based on rule checking, if the percentage
		 * of a TC is too small, the maximum credit may not be
		 * enough to send out a jumbo frame in data plane arbitration.
		 */
		if (credit_max < min_credit)
			credit_max = min_credit;

		if (direction == IXGBE_DCB_TX_CONFIG) {
			/*
			 * Adjustment based on rule checking, if the
			 * percentage of a TC is too small, the maximum
			 * credit may not be enough to send out a TSO
			 * packet in descriptor plane arbitration.
			 */
			if (credit_max && (credit_max <
			    IXGBE_DCB_MIN_TSO_CREDIT)
			    && (hw->mac.type == ixgbe_mac_82598EB))
				credit_max = IXGBE_DCB_MIN_TSO_CREDIT;

			dcb_config->tc_config[i].desc_credits_max =
								(u16)credit_max;
		}

		p->data_credits_max = (u16)credit_max;
	}

out:
	return ret_val;
}