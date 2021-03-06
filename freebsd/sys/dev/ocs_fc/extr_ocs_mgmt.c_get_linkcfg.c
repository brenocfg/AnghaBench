#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
typedef  scalar_t__ ocs_hw_linkcfg_e ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RW ; 
 int /*<<< orphan*/  OCS_HW_LINKCFG ; 
 int /*<<< orphan*/  ocs_hw_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ocs_mgmt_emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 char* ocs_mgmt_from_hw_linkcfg (scalar_t__) ; 

__attribute__((used)) static void
get_linkcfg(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	const char *linkcfg_str = NULL;
	uint32_t value;
	ocs_hw_linkcfg_e linkcfg;
	ocs_hw_get(&ocs->hw, OCS_HW_LINKCFG, &value);
	linkcfg = (ocs_hw_linkcfg_e)value;
	linkcfg_str = ocs_mgmt_from_hw_linkcfg(linkcfg);
	ocs_mgmt_emit_string(textbuf, MGMT_MODE_RW, "linkcfg", linkcfg_str);
}