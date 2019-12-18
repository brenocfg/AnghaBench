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
struct ip_fw_chain {int dummy; } ;
typedef  enum ipfw_sets_cmd { ____Placeholder_ipfw_sets_cmd } ipfw_sets_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
#define  MOVE_ALL 130 
#define  SWAP_ALL 129 
#define  TEST_ALL 128 
 int /*<<< orphan*/  V_fw_tables_sets ; 
 int ipfw_obj_manage_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int table_manage_sets (struct ip_fw_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
table_manage_sets_all(struct ip_fw_chain *ch, uint16_t set, uint8_t new_set,
    enum ipfw_sets_cmd cmd)
{

	switch (cmd) {
	case SWAP_ALL:
	case TEST_ALL:
		/*
		 * Return success for TEST_ALL, since nothing prevents
		 * move rules from one set to another. All tables are
		 * accessible from all sets when per-set tables sysctl
		 * is disabled.
		 */
	case MOVE_ALL:
		if (V_fw_tables_sets == 0)
			return (0);
		break;
	default:
		return (table_manage_sets(ch, set, new_set, cmd));
	}
	/* Use generic sets handler when per-set sysctl is enabled. */
	return (ipfw_obj_manage_sets(CHAIN_TO_NI(ch), IPFW_TLV_TBL_NAME,
	    set, new_set, cmd));
}