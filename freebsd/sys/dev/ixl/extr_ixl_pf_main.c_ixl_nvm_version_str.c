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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sbuf {int dummy; } ;
struct TYPE_4__ {int oem_ver; int version; int /*<<< orphan*/  eetrack; } ;
struct TYPE_3__ {int /*<<< orphan*/  api_min_ver; int /*<<< orphan*/  api_maj_ver; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  fw_min_ver; int /*<<< orphan*/  fw_maj_ver; } ;
struct i40e_hw {TYPE_2__ nvm; TYPE_1__ aq; } ;

/* Variables and functions */
 int IXL_NVM_VERSION_HI_MASK ; 
 int IXL_NVM_VERSION_HI_SHIFT ; 
 int IXL_NVM_VERSION_LO_MASK ; 
 int IXL_NVM_VERSION_LO_SHIFT ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ixl_nvm_version_str(struct i40e_hw *hw, struct sbuf *buf)
{
	u8 oem_ver = (u8)(hw->nvm.oem_ver >> 24);
	u16 oem_build = (u16)((hw->nvm.oem_ver >> 16) & 0xFFFF);
	u8 oem_patch = (u8)(hw->nvm.oem_ver & 0xFF);

	sbuf_printf(buf,
	    "fw %d.%d.%05d api %d.%d nvm %x.%02x etid %08x oem %d.%d.%d",
	    hw->aq.fw_maj_ver, hw->aq.fw_min_ver, hw->aq.fw_build,
	    hw->aq.api_maj_ver, hw->aq.api_min_ver,
	    (hw->nvm.version & IXL_NVM_VERSION_HI_MASK) >>
	    IXL_NVM_VERSION_HI_SHIFT,
	    (hw->nvm.version & IXL_NVM_VERSION_LO_MASK) >>
	    IXL_NVM_VERSION_LO_SHIFT,
	    hw->nvm.eetrack,
	    oem_ver, oem_build, oem_patch);
}