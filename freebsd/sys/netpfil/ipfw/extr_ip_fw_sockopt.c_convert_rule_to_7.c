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
typedef  int /*<<< orphan*/  uint32_t ;
struct ip_fw_rule0 {int cmd_len; scalar_t__ opcode; struct ip_fw_rule0* cmd; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; scalar_t__ next_rule; int /*<<< orphan*/  act_ofs; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  set; } ;
struct ip_fw7 {int cmd_len; struct ip_fw_rule0* cmd; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; struct ip_fw7* next_rule; int /*<<< orphan*/  act_ofs; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  set; } ;
typedef  struct ip_fw_rule0 ipfw_insn ;

/* Variables and functions */
 int EINVAL ; 
 int F_LEN (struct ip_fw_rule0*) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 scalar_t__ O_NAT ; 
 int RULE_MAXSIZE ; 
 int /*<<< orphan*/  bcopy (struct ip_fw_rule0*,struct ip_fw_rule0*,int) ; 
 int /*<<< orphan*/  free (struct ip_fw_rule0*,int /*<<< orphan*/ ) ; 
 struct ip_fw_rule0* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static int
convert_rule_to_7(struct ip_fw_rule0 *rule)
{
	/* Used to modify original rule */
	struct ip_fw7 *rule7 = (struct ip_fw7 *)rule;
	/* copy of original rule, version 8 */
	struct ip_fw_rule0 *tmp;

	/* Used to copy commands */
	ipfw_insn *ccmd, *dst;
	int ll = 0, ccmdlen = 0;

	tmp = malloc(RULE_MAXSIZE, M_TEMP, M_NOWAIT | M_ZERO);
	if (tmp == NULL) {
		return 1; //XXX error
	}
	bcopy(rule, tmp, RULE_MAXSIZE);

	/* Copy fields */
	//rule7->_pad = tmp->_pad;
	rule7->set = tmp->set;
	rule7->rulenum = tmp->rulenum;
	rule7->cmd_len = tmp->cmd_len;
	rule7->act_ofs = tmp->act_ofs;
	rule7->next_rule = (struct ip_fw7 *)tmp->next_rule;
	rule7->cmd_len = tmp->cmd_len;
	rule7->pcnt = tmp->pcnt;
	rule7->bcnt = tmp->bcnt;
	rule7->timestamp = tmp->timestamp;

	/* Copy commands */
	for (ll = tmp->cmd_len, ccmd = tmp->cmd, dst = rule7->cmd ;
			ll > 0 ; ll -= ccmdlen, ccmd += ccmdlen, dst += ccmdlen) {
		ccmdlen = F_LEN(ccmd);

		bcopy(ccmd, dst, F_LEN(ccmd)*sizeof(uint32_t));

		if (dst->opcode > O_NAT)
			/* O_REASS doesn't exists in 7.2 version, so
			 * decrement opcode if it is after O_REASS
			 */
			dst->opcode--;

		if (ccmdlen > ll) {
			printf("ipfw: opcode %d size truncated\n",
				ccmd->opcode);
			return EINVAL;
		}
	}
	free(tmp, M_TEMP);

	return 0;
}