#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int mtu; int rate; } ;
struct TYPE_7__ {TYPE_1__ mcmember_rec; } ;
typedef  TYPE_2__ osm_mgrp_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int ib_net64_t ;
struct TYPE_8__ {int mtu; int rate; } ;
typedef  TYPE_3__ ib_member_rec_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IB_MCR_COMPMASK_MTU_SEL ; 
 int IB_MCR_COMPMASK_RATE_SEL ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ib_path_compare_rates (int,int) ; 

__attribute__((used)) static boolean_t validate_more_comp_fields(osm_log_t * p_log,
					   const osm_mgrp_t * p_mgrp,
					   const ib_member_rec_t *
					   p_recvd_mcmember_rec,
					   ib_net64_t comp_mask)
{
	uint8_t mtu_sel;
	uint8_t mtu_required;
	uint8_t mtu_mgrp;
	uint8_t rate_sel;
	uint8_t rate_required;
	uint8_t rate_mgrp;

	if (comp_mask & IB_MCR_COMPMASK_MTU_SEL) {
		mtu_sel = (uint8_t) (p_recvd_mcmember_rec->mtu >> 6);
		/* Clearing last 2 bits */
		mtu_required = (uint8_t) (p_recvd_mcmember_rec->mtu & 0x3F);
		mtu_mgrp = (uint8_t) (p_mgrp->mcmember_rec.mtu & 0x3F);
		switch (mtu_sel) {
		case 0:	/* Greater than MTU specified */
			if (mtu_mgrp <= mtu_required) {
				OSM_LOG(p_log, OSM_LOG_VERBOSE,
					"Requested mcast group has MTU %x, "
					"which is not greater than %x\n",
					mtu_mgrp, mtu_required);
				return FALSE;
			}
			break;
		case 1:	/* Less than MTU specified */
			if (mtu_mgrp >= mtu_required) {
				OSM_LOG(p_log, OSM_LOG_VERBOSE,
					"Requested mcast group has MTU %x, "
					"which is not less than %x\n",
					mtu_mgrp, mtu_required);
				return FALSE;
			}
			break;
		case 2:	/* Exactly MTU specified */
			if (mtu_mgrp != mtu_required) {
				OSM_LOG(p_log, OSM_LOG_VERBOSE,
					"Requested mcast group has MTU %x, "
					"which is not equal to %x\n",
					mtu_mgrp, mtu_required);
				return FALSE;
			}
			break;
		default:
			break;
		}
	}

	/* what about rate ? */
	if (comp_mask & IB_MCR_COMPMASK_RATE_SEL) {
		rate_sel = (uint8_t) (p_recvd_mcmember_rec->rate >> 6);
		/* Clearing last 2 bits */
		rate_required = (uint8_t) (p_recvd_mcmember_rec->rate & 0x3F);
		rate_mgrp = (uint8_t) (p_mgrp->mcmember_rec.rate & 0x3F);
		switch (rate_sel) {
		case 0:	/* Greater than RATE specified */
			if (ib_path_compare_rates(rate_mgrp, rate_required) <= 0) {
				OSM_LOG(p_log, OSM_LOG_VERBOSE,
					"Requested mcast group has RATE %x, "
					"which is not greater than %x\n",
					rate_mgrp, rate_required);
				return FALSE;
			}
			break;
		case 1:	/* Less than RATE specified */
			if (ib_path_compare_rates(rate_mgrp, rate_required) >= 0) {
				OSM_LOG(p_log, OSM_LOG_VERBOSE,
					"Requested mcast group has RATE %x, "
					"which is not less than %x\n",
					rate_mgrp, rate_required);
				return FALSE;
			}
			break;
		case 2:	/* Exactly RATE specified */
			if (ib_path_compare_rates(rate_mgrp, rate_required)) {
				OSM_LOG(p_log, OSM_LOG_VERBOSE,
					"Requested mcast group has RATE %x, "
					"which is not equal to %x\n",
					rate_mgrp, rate_required);
				return FALSE;
			}
			break;
		default:
			break;
		}
	}

	return TRUE;
}