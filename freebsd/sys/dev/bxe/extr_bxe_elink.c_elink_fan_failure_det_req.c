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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct elink_phy {scalar_t__ flags; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ ELINK_EXT_PHY1 ; 
 scalar_t__ ELINK_FLAGS_FAN_FAILURE_DET_REQ ; 
 scalar_t__ ELINK_MAX_PHYS ; 
 scalar_t__ ELINK_STATUS_OK ; 
 scalar_t__ elink_populate_phy (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct elink_phy*) ; 

uint8_t elink_fan_failure_det_req(struct bxe_softc *sc,
			     uint32_t shmem_base,
			     uint32_t shmem2_base,
			     uint8_t port)
{
	uint8_t phy_index, fan_failure_det_req = 0;
	struct elink_phy phy;
	for (phy_index = ELINK_EXT_PHY1; phy_index < ELINK_MAX_PHYS;
	      phy_index++) {
		if (elink_populate_phy(sc, phy_index, shmem_base, shmem2_base,
				       port, &phy)
		    != ELINK_STATUS_OK) {
			ELINK_DEBUG_P0(sc, "populate phy failed\n");
			return 0;
		}
		fan_failure_det_req |= (phy.flags &
					ELINK_FLAGS_FAN_FAILURE_DET_REQ);
	}
	return fan_failure_det_req;
}