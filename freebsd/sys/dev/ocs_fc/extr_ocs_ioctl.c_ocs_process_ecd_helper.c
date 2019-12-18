#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_19__ {int /*<<< orphan*/  dev; TYPE_1__* reg; } ;
typedef  TYPE_2__ ocs_t ;
struct TYPE_20__ {int cmd; size_t bar; int /*<<< orphan*/  data; int /*<<< orphan*/  offset; } ;
typedef  TYPE_3__ ocs_ioctl_ecd_helper_t ;
typedef  int int32_t ;
struct TYPE_18__ {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int EFAULT ; 
#define  OCS_ECD_HELPER_BAR_READ16 139 
#define  OCS_ECD_HELPER_BAR_READ32 138 
#define  OCS_ECD_HELPER_BAR_READ8 137 
#define  OCS_ECD_HELPER_BAR_WRITE16 136 
#define  OCS_ECD_HELPER_BAR_WRITE32 135 
#define  OCS_ECD_HELPER_BAR_WRITE8 134 
#define  OCS_ECD_HELPER_CFG_READ16 133 
#define  OCS_ECD_HELPER_CFG_READ32 132 
#define  OCS_ECD_HELPER_CFG_READ8 131 
#define  OCS_ECD_HELPER_CFG_WRITE16 130 
#define  OCS_ECD_HELPER_CFG_WRITE32 129 
#define  OCS_ECD_HELPER_CFG_WRITE8 128 
 size_t PCI_MAX_BAR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ocs_config_read16 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_read32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_read8 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_write16 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_write32 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_write8 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_reg_read16 (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_reg_read32 (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_reg_read8 (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_reg_write16 (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_reg_write32 (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_reg_write8 (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ocs_process_ecd_helper (ocs_t *ocs, ocs_ioctl_ecd_helper_t *req)
{
	int32_t rc = 0;
	uint8_t v8;
	uint16_t v16;
	uint32_t v32;


	/* Check the BAR read/write commands for valid bar */
	switch(req->cmd) {
	case OCS_ECD_HELPER_BAR_READ8:
	case OCS_ECD_HELPER_BAR_READ16:
	case OCS_ECD_HELPER_BAR_READ32:
	case OCS_ECD_HELPER_BAR_WRITE8:
	case OCS_ECD_HELPER_BAR_WRITE16:
	case OCS_ECD_HELPER_BAR_WRITE32:
		if (req->bar >= PCI_MAX_BAR) {
			device_printf(ocs->dev, "Error: bar %d out of range\n", req->bar);
			return -EFAULT;
		}
		if (ocs->reg[req->bar].res == NULL) {
			device_printf(ocs->dev, "Error: bar %d not defined\n", req->bar);
			return -EFAULT;
		}
		break;
	default:
		break;
	}

	switch(req->cmd) {
	case OCS_ECD_HELPER_CFG_READ8:
		v8 = ocs_config_read8(ocs, req->offset);
		req->data = v8;
		break;
	case OCS_ECD_HELPER_CFG_READ16:
		v16 = ocs_config_read16(ocs, req->offset);
		req->data = v16;
		break;
	case OCS_ECD_HELPER_CFG_READ32:
		v32 = ocs_config_read32(ocs, req->offset);
		req->data = v32;
		break;
	case OCS_ECD_HELPER_CFG_WRITE8:
		ocs_config_write8(ocs, req->offset, req->data);
		break;
	case OCS_ECD_HELPER_CFG_WRITE16:
		ocs_config_write16(ocs, req->offset, req->data);
		break;
	case OCS_ECD_HELPER_CFG_WRITE32:
		ocs_config_write32(ocs, req->offset, req->data);
		break;
	case OCS_ECD_HELPER_BAR_READ8:
		req->data = ocs_reg_read8(ocs, req->bar, req->offset);
		break;
	case OCS_ECD_HELPER_BAR_READ16:
		req->data = ocs_reg_read16(ocs, req->bar, req->offset);
		break;
	case OCS_ECD_HELPER_BAR_READ32:
		req->data = ocs_reg_read32(ocs, req->bar, req->offset);
		break;
	case OCS_ECD_HELPER_BAR_WRITE8:
		ocs_reg_write8(ocs, req->bar, req->offset, req->data);
		break;
	case OCS_ECD_HELPER_BAR_WRITE16:
		ocs_reg_write16(ocs, req->bar, req->offset, req->data);
		break;
	case OCS_ECD_HELPER_BAR_WRITE32:
		ocs_reg_write32(ocs, req->bar, req->offset, req->data);
		break;
	default:
		device_printf(ocs->dev, "Invalid helper command=%d\n", req->cmd);
		break;
	}

	return rc;
}