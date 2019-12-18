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
typedef  scalar_t__ uint16_t ;
struct tid_info {int dummy; } ;
struct rule_check_info {scalar_t__ object_opcodes; } ;
struct obj_idx {int off; } ;
struct ip_fw_chain {int dummy; } ;
struct ip_fw {int cmd_len; int /*<<< orphan*/ * cmd; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int F_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int create_objects_compat (struct ip_fw_chain*,int /*<<< orphan*/ *,struct obj_idx*,struct obj_idx*,struct tid_info*) ; 
 int ref_opcode_object (struct ip_fw_chain*,int /*<<< orphan*/ *,struct tid_info*,struct obj_idx*,int*) ; 
 int /*<<< orphan*/  unref_oib_objects (struct ip_fw_chain*,int /*<<< orphan*/ *,struct obj_idx*,struct obj_idx*) ; 

__attribute__((used)) static int
ref_rule_objects(struct ip_fw_chain *ch, struct ip_fw *rule,
    struct rule_check_info *ci, struct obj_idx *oib, struct tid_info *ti)
{
	struct obj_idx *pidx;
	ipfw_insn *cmd;
	int cmdlen, error, l, unresolved;

	pidx = oib;
	l = rule->cmd_len;
	cmd = rule->cmd;
	cmdlen = 0;
	error = 0;

	IPFW_UH_WLOCK(ch);

	/* Increase refcount on each existing referenced table. */
	for ( ;	l > 0 ; l -= cmdlen, cmd += cmdlen) {
		cmdlen = F_LEN(cmd);
		unresolved = 0;

		error = ref_opcode_object(ch, cmd, ti, pidx, &unresolved);
		if (error != 0)
			break;
		/*
		 * Compatibility stuff for old clients:
		 * prepare to automaitcally create non-existing objects.
		 */
		if (unresolved != 0) {
			pidx->off = rule->cmd_len - l;
			pidx++;
		}
	}

	if (error != 0) {
		/* Unref everything we have already done */
		unref_oib_objects(ch, rule->cmd, oib, pidx);
		IPFW_UH_WUNLOCK(ch);
		return (error);
	}
	IPFW_UH_WUNLOCK(ch);

	/* Perform auto-creation for non-existing objects */
	if (pidx != oib)
		error = create_objects_compat(ch, rule->cmd, oib, pidx, ti);

	/* Calculate real number of dynamic objects */
	ci->object_opcodes = (uint16_t)(pidx - oib);

	return (error);
}