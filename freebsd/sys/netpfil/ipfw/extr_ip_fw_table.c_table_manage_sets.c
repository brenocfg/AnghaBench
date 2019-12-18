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
#define  COUNT_ONE 133 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
#define  MOVE_ALL 132 
#define  MOVE_ONE 131 
#define  SWAP_ALL 130 
#define  TEST_ALL 129 
#define  TEST_ONE 128 
 int /*<<< orphan*/  V_fw_tables_sets ; 
 int ipfw_obj_manage_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
table_manage_sets(struct ip_fw_chain *ch, uint16_t set, uint8_t new_set,
    enum ipfw_sets_cmd cmd)
{

	switch (cmd) {
	case SWAP_ALL:
	case TEST_ALL:
	case MOVE_ALL:
		/*
		 * Always return success, the real action and decision
		 * should make table_manage_sets_all().
		 */
		return (0);
	case TEST_ONE:
	case MOVE_ONE:
		/*
		 * NOTE: we need to use ipfw_objhash_del/ipfw_objhash_add
		 * if set number will be used in hash function. Currently
		 * we can just use generic handler that replaces set value.
		 */
		if (V_fw_tables_sets == 0)
			return (0);
		break;
	case COUNT_ONE:
		/*
		 * Return EOPNOTSUPP for COUNT_ONE when per-set sysctl is
		 * disabled. This allow skip table's opcodes from additional
		 * checks when specific rules moved to another set.
		 */
		if (V_fw_tables_sets == 0)
			return (EOPNOTSUPP);
	}
	/* Use generic sets handler when per-set sysctl is enabled. */
	return (ipfw_obj_manage_sets(CHAIN_TO_NI(ch), IPFW_TLV_TBL_NAME,
	    set, new_set, cmd));
}