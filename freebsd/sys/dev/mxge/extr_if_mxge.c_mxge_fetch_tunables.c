#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ throttle; scalar_t__ pause; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 scalar_t__ ETHERMTU_JUMBO ; 
 scalar_t__ ETHER_MIN_LEN ; 
 scalar_t__ MXGEFW_RSS_HASH_TYPE_IPV4 ; 
 scalar_t__ MXGEFW_RSS_HASH_TYPE_MAX ; 
 scalar_t__ MXGEFW_RSS_HASH_TYPE_SRC_DST_PORT ; 
 scalar_t__ MXGE_MAX_THROTTLE ; 
 scalar_t__ MXGE_MIN_THROTTLE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,...) ; 
 scalar_t__ bootverbose ; 
 int hz ; 
 scalar_t__ mxge_always_promisc ; 
 scalar_t__ mxge_deassert_wait ; 
 scalar_t__ mxge_flow_control ; 
 scalar_t__ mxge_force_firmware ; 
 scalar_t__ mxge_initial_mtu ; 
 int mxge_intr_coal_delay ; 
 scalar_t__ mxge_max_slices ; 
 scalar_t__ mxge_nvidia_ecrc_enable ; 
 scalar_t__ mxge_rss_hash_type ; 
 scalar_t__ mxge_throttle ; 
 scalar_t__ mxge_ticks ; 
 scalar_t__ mxge_verbose ; 

__attribute__((used)) static void
mxge_fetch_tunables(mxge_softc_t *sc)
{

	TUNABLE_INT_FETCH("hw.mxge.max_slices", &mxge_max_slices);
	TUNABLE_INT_FETCH("hw.mxge.flow_control_enabled",
			  &mxge_flow_control);
	TUNABLE_INT_FETCH("hw.mxge.intr_coal_delay",
			  &mxge_intr_coal_delay);	
	TUNABLE_INT_FETCH("hw.mxge.nvidia_ecrc_enable",
			  &mxge_nvidia_ecrc_enable);	
	TUNABLE_INT_FETCH("hw.mxge.force_firmware",
			  &mxge_force_firmware);	
	TUNABLE_INT_FETCH("hw.mxge.deassert_wait",
			  &mxge_deassert_wait);	
	TUNABLE_INT_FETCH("hw.mxge.verbose",
			  &mxge_verbose);	
	TUNABLE_INT_FETCH("hw.mxge.ticks", &mxge_ticks);
	TUNABLE_INT_FETCH("hw.mxge.always_promisc", &mxge_always_promisc);
	TUNABLE_INT_FETCH("hw.mxge.rss_hash_type", &mxge_rss_hash_type);
	TUNABLE_INT_FETCH("hw.mxge.rss_hashtype", &mxge_rss_hash_type);
	TUNABLE_INT_FETCH("hw.mxge.initial_mtu", &mxge_initial_mtu);
	TUNABLE_INT_FETCH("hw.mxge.throttle", &mxge_throttle);

	if (bootverbose)
		mxge_verbose = 1;
	if (mxge_intr_coal_delay < 0 || mxge_intr_coal_delay > 10*1000)
		mxge_intr_coal_delay = 30;
	if (mxge_ticks == 0)
		mxge_ticks = hz / 2;
	sc->pause = mxge_flow_control;
	if (mxge_rss_hash_type < MXGEFW_RSS_HASH_TYPE_IPV4
	    || mxge_rss_hash_type > MXGEFW_RSS_HASH_TYPE_MAX) {
		mxge_rss_hash_type = MXGEFW_RSS_HASH_TYPE_SRC_DST_PORT;
	}
	if (mxge_initial_mtu > ETHERMTU_JUMBO ||
	    mxge_initial_mtu < ETHER_MIN_LEN)
		mxge_initial_mtu = ETHERMTU_JUMBO;

	if (mxge_throttle && mxge_throttle > MXGE_MAX_THROTTLE)
		mxge_throttle = MXGE_MAX_THROTTLE;
	if (mxge_throttle && mxge_throttle < MXGE_MIN_THROTTLE)
		mxge_throttle = MXGE_MIN_THROTTLE;
	sc->throttle = mxge_throttle;
}