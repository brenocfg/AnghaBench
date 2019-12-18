#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cmd; int /*<<< orphan*/  width; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ qlnx_pcicfg_rd_wr_t ;
struct TYPE_6__ {int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
#define  QLNX_PCICFG_READ 129 
#define  QLNX_PCICFG_WRITE 128 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_rd_wr_pci_config(qlnx_host_t *ha, qlnx_pcicfg_rd_wr_t *pci_cfg_rd_wr)
{
	int rval = 0;

	switch (pci_cfg_rd_wr->cmd) {

		case QLNX_PCICFG_READ:
			pci_cfg_rd_wr->val = pci_read_config(ha->pci_dev,
						pci_cfg_rd_wr->reg,
						pci_cfg_rd_wr->width);
			break;

		case QLNX_PCICFG_WRITE:
			pci_write_config(ha->pci_dev, pci_cfg_rd_wr->reg,
				pci_cfg_rd_wr->val, pci_cfg_rd_wr->width);
			break;

		default:
			rval = EINVAL;
			break;
	} 

	return (rval);
}