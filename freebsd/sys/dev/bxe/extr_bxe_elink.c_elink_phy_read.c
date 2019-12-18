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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct elink_params {size_t num_phys; TYPE_1__* phy; int /*<<< orphan*/  sc; } ;
typedef  int /*<<< orphan*/  elink_status_t ;
struct TYPE_2__ {size_t addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  elink_cl45_read (int /*<<< orphan*/ ,TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

elink_status_t elink_phy_read(struct elink_params *params, uint8_t phy_addr,
		   uint8_t devad, uint16_t reg, uint16_t *ret_val)
{
	uint8_t phy_index;
	/* Probe for the phy according to the given phy_addr, and execute
	 * the read request on it
	 */
	for (phy_index = 0; phy_index < params->num_phys; phy_index++) {
		if (params->phy[phy_index].addr == phy_addr) {
			return elink_cl45_read(params->sc,
					       &params->phy[phy_index], devad,
					       reg, ret_val);
		}
	}
	return ELINK_STATUS_ERROR;
}