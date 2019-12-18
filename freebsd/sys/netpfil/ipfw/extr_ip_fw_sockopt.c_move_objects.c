#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct opcode_obj_rewrite {int (* manage_sets ) (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct ip_fw_chain {int n_rules; struct ip_fw** map; } ;
struct ip_fw {scalar_t__ set; int cmd_len; int /*<<< orphan*/ * cmd; } ;
struct TYPE_4__ {scalar_t__ new_set; } ;
typedef  TYPE_1__ ipfw_range_tlv ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT_ONE ; 
 int F_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  MOVE_ONE ; 
 int /*<<< orphan*/  TEST_ONE ; 
 struct opcode_obj_rewrite* find_op_rw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipfw_match_range (struct ip_fw*,TYPE_1__*) ; 
 int stub1 (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub3 (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub4 (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
move_objects(struct ip_fw_chain *ch, ipfw_range_tlv *rt)
{
	struct opcode_obj_rewrite *rw;
	struct ip_fw *rule;
	ipfw_insn *cmd;
	int cmdlen, i, l, c;
	uint16_t kidx;

	IPFW_UH_WLOCK_ASSERT(ch);

	/* Stage 1: count number of references by given rules */
	for (c = 0, i = 0; i < ch->n_rules - 1; i++) {
		rule = ch->map[i];
		if (ipfw_match_range(rule, rt) == 0)
			continue;
		if (rule->set == rt->new_set) /* nothing to do */
			continue;
		/* Search opcodes with named objects */
		for (l = rule->cmd_len, cmdlen = 0, cmd = rule->cmd;
		    l > 0; l -= cmdlen, cmd += cmdlen) {
			cmdlen = F_LEN(cmd);
			rw = find_op_rw(cmd, &kidx, NULL);
			if (rw == NULL || rw->manage_sets == NULL)
				continue;
			/*
			 * When manage_sets() returns non-zero value to
			 * COUNT_ONE command, consider this as an object
			 * doesn't support sets (e.g. disabled with sysctl).
			 * So, skip checks for this object.
			 */
			if (rw->manage_sets(ch, kidx, 1, COUNT_ONE) != 0)
				continue;
			c++;
		}
	}
	if (c == 0) /* No objects found */
		return (0);
	/* Stage 2: verify "ownership" */
	for (c = 0, i = 0; (i < ch->n_rules - 1) && c == 0; i++) {
		rule = ch->map[i];
		if (ipfw_match_range(rule, rt) == 0)
			continue;
		if (rule->set == rt->new_set) /* nothing to do */
			continue;
		/* Search opcodes with named objects */
		for (l = rule->cmd_len, cmdlen = 0, cmd = rule->cmd;
		    l > 0 && c == 0; l -= cmdlen, cmd += cmdlen) {
			cmdlen = F_LEN(cmd);
			rw = find_op_rw(cmd, &kidx, NULL);
			if (rw == NULL || rw->manage_sets == NULL)
				continue;
			/* Test for ownership and conflicting names */
			c = rw->manage_sets(ch, kidx,
			    (uint8_t)rt->new_set, TEST_ONE);
		}
	}
	/* Stage 3: change set and cleanup */
	for (i = 0; i < ch->n_rules - 1; i++) {
		rule = ch->map[i];
		if (ipfw_match_range(rule, rt) == 0)
			continue;
		if (rule->set == rt->new_set) /* nothing to do */
			continue;
		/* Search opcodes with named objects */
		for (l = rule->cmd_len, cmdlen = 0, cmd = rule->cmd;
		    l > 0; l -= cmdlen, cmd += cmdlen) {
			cmdlen = F_LEN(cmd);
			rw = find_op_rw(cmd, &kidx, NULL);
			if (rw == NULL || rw->manage_sets == NULL)
				continue;
			/* cleanup object counter */
			rw->manage_sets(ch, kidx,
			    0 /* reset counter */, COUNT_ONE);
			if (c != 0)
				continue;
			/* change set */
			rw->manage_sets(ch, kidx,
			    (uint8_t)rt->new_set, MOVE_ONE);
		}
	}
	return (c);
}