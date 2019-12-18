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
typedef  int /*<<< orphan*/  uint8_t ;
struct al_serdes_grp_obj {int dummy; } ;
typedef  enum al_serdes_reg_page { ____Placeholder_al_serdes_reg_page } al_serdes_reg_page ;
typedef  enum al_serdes_lane { ____Placeholder_al_serdes_lane } al_serdes_lane ;
typedef  int al_bool ;

/* Variables and functions */
 int /*<<< orphan*/  SERDES_25G_LANE_CDR_RXCLK_DLPF_STATUS5_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_CDR_RXCLK_DLPF_STATUS5_LOCKED_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_CDR_RXCLK_DLPF_STATUS5_LOCKED_SHIFT ; 
 int /*<<< orphan*/  al_serdes_25g_reg_masked_read (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static al_bool al_serdes_25g_cdr_is_locked(
		struct al_serdes_grp_obj	*obj,
		enum al_serdes_lane		lane)
{
	uint8_t reg;

	al_serdes_25g_reg_masked_read(obj,
				(enum al_serdes_reg_page)lane,
				SERDES_25G_LANE_CDR_RXCLK_DLPF_STATUS5_ADDR,
				SERDES_25G_LANE_CDR_RXCLK_DLPF_STATUS5_LOCKED_MASK,
				SERDES_25G_LANE_CDR_RXCLK_DLPF_STATUS5_LOCKED_SHIFT,
				&reg);

	return !!reg;

}