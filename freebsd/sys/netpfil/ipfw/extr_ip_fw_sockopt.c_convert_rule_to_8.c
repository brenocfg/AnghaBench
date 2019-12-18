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
struct ip_fw_rule0 {int cmd_len; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; scalar_t__ id; struct ip_fw* next_rule; int /*<<< orphan*/  act_ofs; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  set; int /*<<< orphan*/  _pad; struct ip_fw7* cmd; } ;
struct ip_fw7 {int cmd_len; scalar_t__ opcode; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; scalar_t__ next_rule; int /*<<< orphan*/  act_ofs; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  set; int /*<<< orphan*/  _pad; struct ip_fw7* cmd; } ;
struct ip_fw {int dummy; } ;
typedef  struct ip_fw7 ipfw_insn ;

/* Variables and functions */
 int EINVAL ; 
 int F_LEN (struct ip_fw7*) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 scalar_t__ O_NAT ; 
 int RULE_MAXSIZE ; 
 int /*<<< orphan*/  bcopy (struct ip_fw7*,struct ip_fw7*,int) ; 
 int /*<<< orphan*/  free (struct ip_fw7*,int /*<<< orphan*/ ) ; 
 struct ip_fw7* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static int
convert_rule_to_8(struct ip_fw_rule0 *rule)
{
	/* Used to modify original rule */
	struct ip_fw7 *rule7 = (struct ip_fw7 *) rule;

	/* Used to copy commands */
	ipfw_insn *ccmd, *dst;
	int ll = 0, ccmdlen = 0;

	/* Copy of original rule */
	struct ip_fw7 *tmp = malloc(RULE_MAXSIZE, M_TEMP, M_NOWAIT | M_ZERO);
	if (tmp == NULL) {
		return 1; //XXX error
	}

	bcopy(rule7, tmp, RULE_MAXSIZE);

	for (ll = tmp->cmd_len, ccmd = tmp->cmd, dst = rule->cmd ;
			ll > 0 ; ll -= ccmdlen, ccmd += ccmdlen, dst += ccmdlen) {
		ccmdlen = F_LEN(ccmd);
		
		bcopy(ccmd, dst, F_LEN(ccmd)*sizeof(uint32_t));

		if (dst->opcode > O_NAT)
			/* O_REASS doesn't exists in 7.2 version, so
			 * increment opcode if it is after O_REASS
			 */
			dst->opcode++;

		if (ccmdlen > ll) {
			printf("ipfw: opcode %d size truncated\n",
			    ccmd->opcode);
			return EINVAL;
		}
	}

	rule->_pad = tmp->_pad;
	rule->set = tmp->set;
	rule->rulenum = tmp->rulenum;
	rule->cmd_len = tmp->cmd_len;
	rule->act_ofs = tmp->act_ofs;
	rule->next_rule = (struct ip_fw *)tmp->next_rule;
	rule->cmd_len = tmp->cmd_len;
	rule->id = 0; /* XXX see if is ok = 0 */
	rule->pcnt = tmp->pcnt;
	rule->bcnt = tmp->bcnt;
	rule->timestamp = tmp->timestamp;

	free (tmp, M_TEMP);
	return 0;
}