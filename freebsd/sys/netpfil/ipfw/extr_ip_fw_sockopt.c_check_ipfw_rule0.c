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
struct rule_check_info {int dummy; } ;
struct ip_fw_rule0 {int cmd_len; int act_ofs; int rulenum; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPFW_DEFAULT_RULE ; 
 int check_ipfw_rule_body (int /*<<< orphan*/ ,int,struct rule_check_info*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
check_ipfw_rule0(struct ip_fw_rule0 *rule, int size,
    struct rule_check_info *ci)
{
	int l;

	if (size < sizeof(*rule)) {
		printf("ipfw: rule too short\n");
		return (EINVAL);
	}

	/* Check for valid cmd_len */
	l = sizeof(*rule) + rule->cmd_len * 4 - 4;
	if (l != size) {
		printf("ipfw: size mismatch (have %d want %d)\n", size, l);
		return (EINVAL);
	}
	if (rule->act_ofs >= rule->cmd_len) {
		printf("ipfw: bogus action offset (%u > %u)\n",
		    rule->act_ofs, rule->cmd_len - 1);
		return (EINVAL);
	}

	if (rule->rulenum > IPFW_DEFAULT_RULE - 1)
		return (EINVAL);

	return (check_ipfw_rule_body(rule->cmd, rule->cmd_len, ci));
}