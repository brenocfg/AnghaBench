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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  hdr_split; } ;
struct TYPE_4__ {TYPE_1__ rfw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AL_TRUE ; 
 int /*<<< orphan*/  EC_RFW_HDR_SPLIT_DEF_LEN_MASK ; 
 int /*<<< orphan*/  EC_RFW_HDR_SPLIT_DEF_LEN_SHIFT ; 
 int /*<<< orphan*/  EC_RFW_HDR_SPLIT_EN ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_rx_header_split_config(struct al_hal_eth_adapter *adapter, al_bool enable, uint32_t header_len)
{
	uint32_t	reg;

	reg = al_reg_read32(&adapter->ec_regs_base->rfw.hdr_split);
	if (enable == AL_TRUE)
		reg |= EC_RFW_HDR_SPLIT_EN;
	else
		reg &= ~EC_RFW_HDR_SPLIT_EN;

	AL_REG_FIELD_SET(reg, EC_RFW_HDR_SPLIT_DEF_LEN_MASK, EC_RFW_HDR_SPLIT_DEF_LEN_SHIFT, header_len);
	al_reg_write32(&adapter->ec_regs_base->rfw.hdr_split, reg);
	return 0;
}