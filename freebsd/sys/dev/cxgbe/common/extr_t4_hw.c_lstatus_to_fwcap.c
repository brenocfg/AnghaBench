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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PORT_CAP32_FC_RX ; 
 int /*<<< orphan*/  FW_PORT_CAP32_FC_TX ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_100G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_100M ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_10G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_1G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_25G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_40G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_100G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_100M ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_10G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_1G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_25G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_40G ; 
 int F_FW_PORT_CMD_RXPAUSE ; 
 int F_FW_PORT_CMD_TXPAUSE ; 
 int V_FW_PORT_CMD_LSPEED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t lstatus_to_fwcap(u32 lstatus)
{
	uint32_t linkattr = 0;

	/*
	 * Unfortunately the format of the Link Status in the old
	 * 16-bit Port Information message isn't the same as the
	 * 16-bit Port Capabilities bitfield used everywhere else ...
	 */
	if (lstatus & F_FW_PORT_CMD_RXPAUSE)
		linkattr |= FW_PORT_CAP32_FC_RX;
	if (lstatus & F_FW_PORT_CMD_TXPAUSE)
		linkattr |= FW_PORT_CAP32_FC_TX;
	if (lstatus & V_FW_PORT_CMD_LSPEED(FW_PORT_CAP_SPEED_100M))
		linkattr |= FW_PORT_CAP32_SPEED_100M;
	if (lstatus & V_FW_PORT_CMD_LSPEED(FW_PORT_CAP_SPEED_1G))
		linkattr |= FW_PORT_CAP32_SPEED_1G;
	if (lstatus & V_FW_PORT_CMD_LSPEED(FW_PORT_CAP_SPEED_10G))
		linkattr |= FW_PORT_CAP32_SPEED_10G;
	if (lstatus & V_FW_PORT_CMD_LSPEED(FW_PORT_CAP_SPEED_25G))
		linkattr |= FW_PORT_CAP32_SPEED_25G;
	if (lstatus & V_FW_PORT_CMD_LSPEED(FW_PORT_CAP_SPEED_40G))
		linkattr |= FW_PORT_CAP32_SPEED_40G;
	if (lstatus & V_FW_PORT_CMD_LSPEED(FW_PORT_CAP_SPEED_100G))
		linkattr |= FW_PORT_CAP32_SPEED_100G;

	return linkattr;
}