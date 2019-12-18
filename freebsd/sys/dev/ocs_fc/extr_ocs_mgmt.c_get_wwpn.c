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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  OCS_HW_WWN_PORT ; 
 scalar_t__ ocs_htobe64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocs_hw_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_mgmt_emit_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,unsigned long long) ; 

__attribute__((used)) static void
get_wwpn(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	uint64_t *wwpn;

	wwpn = ocs_hw_get_ptr(&ocs->hw, OCS_HW_WWN_PORT);

	ocs_mgmt_emit_int(textbuf, MGMT_MODE_RD, "wwpn", "0x%llx", (unsigned long long)ocs_htobe64(*wwpn));
}