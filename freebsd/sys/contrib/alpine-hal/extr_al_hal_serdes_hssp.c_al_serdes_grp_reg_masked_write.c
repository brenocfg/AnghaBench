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
typedef  int /*<<< orphan*/  uint16_t ;
struct al_serdes_grp_obj {int dummy; } ;
typedef  enum al_serdes_reg_type { ____Placeholder_al_serdes_reg_type } al_serdes_reg_type ;
typedef  enum al_serdes_reg_page { ____Placeholder_al_serdes_reg_page } al_serdes_reg_page ;

/* Variables and functions */
 int AL_SRDS_REG_PAGE_0123_LANES_0123 ; 
 int AL_SRDS_REG_PAGE_0_LANE_0 ; 
 int AL_SRDS_REG_PAGE_3_LANE_3 ; 
 int /*<<< orphan*/  al_serdes_grp_reg_read (struct al_serdes_grp_obj*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_serdes_grp_reg_write (struct al_serdes_grp_obj*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void al_serdes_grp_reg_masked_write(
	struct al_serdes_grp_obj	*obj,
	enum al_serdes_reg_page		page,
	enum al_serdes_reg_type		type,
	uint16_t			offset,
	uint8_t				mask,
	uint8_t				data)
{
	uint8_t val;
	enum al_serdes_reg_page	start_page = page;
	enum al_serdes_reg_page	end_page   = page;
	enum al_serdes_reg_page	iter_page;

	if (page == AL_SRDS_REG_PAGE_0123_LANES_0123) {
		start_page = AL_SRDS_REG_PAGE_0_LANE_0;
		end_page   = AL_SRDS_REG_PAGE_3_LANE_3;
	}

	for (iter_page = start_page; iter_page <= end_page; ++iter_page) {
		val = al_serdes_grp_reg_read(obj, iter_page, type, offset);
		val &= ~mask;
		val |= data;
		al_serdes_grp_reg_write(obj, iter_page, type, offset, val);
	}
}