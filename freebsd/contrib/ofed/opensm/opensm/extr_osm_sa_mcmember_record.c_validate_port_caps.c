#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {int capability_mask; } ;
struct TYPE_10__ {TYPE_4__ port_info; } ;
typedef  TYPE_2__ osm_physp_t ;
struct TYPE_9__ {int mtu; int rate; } ;
struct TYPE_11__ {TYPE_1__ mcmember_rec; } ;
typedef  TYPE_3__ osm_mgrp_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  TYPE_4__ ib_port_info_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IB_PORT_CAP_HAS_EXT_SPEEDS ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ib_path_compare_rates (scalar_t__,scalar_t__) ; 
 scalar_t__ ib_port_info_compute_rate (TYPE_4__ const*,int) ; 
 scalar_t__ ib_port_info_get_neighbor_mtu (TYPE_4__*) ; 

__attribute__((used)) static boolean_t validate_port_caps(osm_log_t * p_log,
				    const osm_mgrp_t * p_mgrp,
				    const osm_physp_t * p_physp)
{
	const ib_port_info_t *p_pi;
	uint8_t mtu_required;
	uint8_t mtu_mgrp;
	uint8_t rate_required;
	uint8_t rate_mgrp;
	int extended;

	mtu_required = ib_port_info_get_neighbor_mtu(&p_physp->port_info);
	mtu_mgrp = (uint8_t) (p_mgrp->mcmember_rec.mtu & 0x3F);
	if (mtu_required < mtu_mgrp) {
		OSM_LOG(p_log, OSM_LOG_VERBOSE,
			"Port's MTU %x is less than %x\n",
			mtu_required, mtu_mgrp);
		return FALSE;
	}

	p_pi = &p_physp->port_info;
	extended = p_pi->capability_mask & IB_PORT_CAP_HAS_EXT_SPEEDS;
	rate_required = ib_port_info_compute_rate(p_pi, extended);
	rate_mgrp = (uint8_t) (p_mgrp->mcmember_rec.rate & 0x3F);
	if (ib_path_compare_rates(rate_required, rate_mgrp) < 0) {
		OSM_LOG(p_log, OSM_LOG_VERBOSE,
			"Port's RATE %x is less than %x\n",
			rate_required, rate_mgrp);
		return FALSE;
	}

	return TRUE;
}