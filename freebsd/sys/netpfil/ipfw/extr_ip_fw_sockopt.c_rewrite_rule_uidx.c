#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ti ;
struct tid_info {scalar_t__ tlen; void* tlvs; int /*<<< orphan*/  set; } ;
struct rule_check_info {int object_opcodes; struct obj_idx* obuf; TYPE_3__* krule; TYPE_2__* ctlv; } ;
struct obj_idx {int off; int /*<<< orphan*/  kidx; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_obj_ctlv ;
typedef  int /*<<< orphan*/  ipfw_insn ;
struct TYPE_6__ {int /*<<< orphan*/ * cmd; int /*<<< orphan*/  set; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_5__ {TYPE_1__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct obj_idx*,int /*<<< orphan*/ ) ; 
 struct obj_idx* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct tid_info*,int /*<<< orphan*/ ,int) ; 
 int ref_rule_objects (struct ip_fw_chain*,TYPE_3__*,struct rule_check_info*,struct obj_idx*,struct tid_info*) ; 
 int /*<<< orphan*/  update_opcode_kidx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rewrite_rule_uidx(struct ip_fw_chain *chain, struct rule_check_info *ci)
{
	int error;
	ipfw_insn *cmd;
	uint8_t type;
	struct obj_idx *p, *pidx_first, *pidx_last;
	struct tid_info ti;

	/*
	 * Prepare an array for storing opcode indices.
	 * Use stack allocation by default.
	 */
	if (ci->object_opcodes <= (sizeof(ci->obuf)/sizeof(ci->obuf[0]))) {
		/* Stack */
		pidx_first = ci->obuf;
	} else
		pidx_first = malloc(
		    ci->object_opcodes * sizeof(struct obj_idx),
		    M_IPFW, M_WAITOK | M_ZERO);

	error = 0;
	type = 0;
	memset(&ti, 0, sizeof(ti));

	/* Use set rule is assigned to. */
	ti.set = ci->krule->set;
	if (ci->ctlv != NULL) {
		ti.tlvs = (void *)(ci->ctlv + 1);
		ti.tlen = ci->ctlv->head.length - sizeof(ipfw_obj_ctlv);
	}

	/* Reference all used tables and other objects */
	error = ref_rule_objects(chain, ci->krule, ci, pidx_first, &ti);
	if (error != 0)
		goto free;
	/*
	 * Note that ref_rule_objects() might have updated ci->object_opcodes
	 * to reflect actual number of object opcodes.
	 */

	/* Perform rewrite of remaining opcodes */
	p = pidx_first;
	pidx_last = pidx_first + ci->object_opcodes;
	for (p = pidx_first; p < pidx_last; p++) {
		cmd = ci->krule->cmd + p->off;
		update_opcode_kidx(cmd, p->kidx);
	}

free:
	if (pidx_first != ci->obuf)
		free(pidx_first, M_IPFW);

	return (error);
}