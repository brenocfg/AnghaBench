#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct tid_info {scalar_t__ atype; int /*<<< orphan*/  type; int /*<<< orphan*/  uidx; } ;
struct opcode_obj_rewrite {int (* create_object ) (struct ip_fw_chain*,struct tid_info*,scalar_t__*) ;} ;
struct obj_idx {scalar_t__ kidx; int off; int /*<<< orphan*/  type; int /*<<< orphan*/  uidx; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct opcode_obj_rewrite* find_op_rw (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (struct ip_fw_chain*,struct tid_info*,scalar_t__*) ; 
 int /*<<< orphan*/  unref_oib_objects (struct ip_fw_chain*,TYPE_1__*,struct obj_idx*,struct obj_idx*) ; 

int
create_objects_compat(struct ip_fw_chain *ch, ipfw_insn *cmd,
    struct obj_idx *oib, struct obj_idx *pidx, struct tid_info *ti)
{
	struct opcode_obj_rewrite *rw;
	struct obj_idx *p;
	uint16_t kidx;
	int error;

	/*
	 * Compatibility stuff: do actual creation for non-existing,
	 * but referenced objects.
	 */
	for (p = oib; p < pidx; p++) {
		if (p->kidx != 0)
			continue;

		ti->uidx = p->uidx;
		ti->type = p->type;
		ti->atype = 0;

		rw = find_op_rw(cmd + p->off, NULL, NULL);
		KASSERT(rw != NULL, ("Unable to find handler for op %d",
		    (cmd + p->off)->opcode));

		if (rw->create_object == NULL)
			error = EOPNOTSUPP;
		else
			error = rw->create_object(ch, ti, &kidx);
		if (error == 0) {
			p->kidx = kidx;
			continue;
		}

		/*
		 * Error happened. We have to rollback everything.
		 * Drop all already acquired references.
		 */
		IPFW_UH_WLOCK(ch);
		unref_oib_objects(ch, cmd, oib, pidx);
		IPFW_UH_WUNLOCK(ch);

		return (error);
	}

	return (0);
}