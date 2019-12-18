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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct opcode_obj_rewrite {int /*<<< orphan*/  (* destroy_object ) (struct ip_fw_chain*,struct named_object*) ;struct named_object* (* find_bykidx ) (struct ip_fw_chain*,int /*<<< orphan*/ ) ;} ;
struct named_object {scalar_t__ subtype; int refcnt; } ;
struct ip_fw_chain {int dummy; } ;
struct ip_fw {int cmd_len; int /*<<< orphan*/ * cmd; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int F_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct opcode_obj_rewrite* find_op_rw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct named_object* stub1 (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ip_fw_chain*,struct named_object*) ; 

__attribute__((used)) static void
unref_rule_objects(struct ip_fw_chain *ch, struct ip_fw *rule)
{
	struct opcode_obj_rewrite *rw;
	struct named_object *no;
	ipfw_insn *cmd;
	int cmdlen, l;
	uint16_t kidx;
	uint8_t subtype;

	IPFW_UH_WLOCK_ASSERT(ch);

	l = rule->cmd_len;
	cmd = rule->cmd;
	cmdlen = 0;
	for ( ;	l > 0 ; l -= cmdlen, cmd += cmdlen) {
		cmdlen = F_LEN(cmd);

		rw = find_op_rw(cmd, &kidx, &subtype);
		if (rw == NULL)
			continue;
		no = rw->find_bykidx(ch, kidx);

		KASSERT(no != NULL, ("object id %d not found", kidx));
		KASSERT(no->subtype == subtype,
		    ("wrong type %d (%d) for object id %d",
		    no->subtype, subtype, kidx));
		KASSERT(no->refcnt > 0, ("refcount for object %d is %d",
		    kidx, no->refcnt));

		if (no->refcnt == 1 && rw->destroy_object != NULL)
			rw->destroy_object(ch, no);
		else
			no->refcnt--;
	}
}