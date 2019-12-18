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
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  SLI4_INTF_REG ; 
 int /*<<< orphan*/  ocs_config_read32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_mgmt_emit_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_sli4_intf_reg(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{

	ocs_mgmt_emit_int(textbuf, MGMT_MODE_RD, "sli4_intf_reg", "0x%04x",
		ocs_config_read32(ocs, SLI4_INTF_REG));
}