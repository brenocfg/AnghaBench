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
struct ipu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IC_CONF ; 
 int /*<<< orphan*/  IDMAC_CHA_BUSY ; 
 int /*<<< orphan*/  IDMAC_CHA_EN ; 
 int /*<<< orphan*/  IDMAC_CHA_PRI ; 
 int /*<<< orphan*/  IDMAC_CONF ; 
 int /*<<< orphan*/  IPU_CHA_BUF0_RDY ; 
 int /*<<< orphan*/  IPU_CHA_BUF1_RDY ; 
 int /*<<< orphan*/  IPU_CHA_CUR_BUF ; 
 int /*<<< orphan*/  IPU_CHA_DB_MODE_SEL ; 
 int /*<<< orphan*/  IPU_TASKS_STAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_read_icreg (struct ipu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_read_ipureg (struct ipu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_idmac_reg(struct ipu *ipu)
{
	dev_dbg(ipu->dev, "IDMAC_CONF 0x%x, IC_CONF 0x%x, IDMAC_CHA_EN 0x%x, "
		"IDMAC_CHA_PRI 0x%x, IDMAC_CHA_BUSY 0x%x\n",
		idmac_read_icreg(ipu, IDMAC_CONF),
		idmac_read_icreg(ipu, IC_CONF),
		idmac_read_icreg(ipu, IDMAC_CHA_EN),
		idmac_read_icreg(ipu, IDMAC_CHA_PRI),
		idmac_read_icreg(ipu, IDMAC_CHA_BUSY));
	dev_dbg(ipu->dev, "BUF0_RDY 0x%x, BUF1_RDY 0x%x, CUR_BUF 0x%x, "
		"DB_MODE 0x%x, TASKS_STAT 0x%x\n",
		idmac_read_ipureg(ipu, IPU_CHA_BUF0_RDY),
		idmac_read_ipureg(ipu, IPU_CHA_BUF1_RDY),
		idmac_read_ipureg(ipu, IPU_CHA_CUR_BUF),
		idmac_read_ipureg(ipu, IPU_CHA_DB_MODE_SEL),
		idmac_read_ipureg(ipu, IPU_TASKS_STAT));
}