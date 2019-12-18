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
struct tid_info {scalar_t__ type; int /*<<< orphan*/  uidx; } ;
struct opcode_obj_rewrite {int (* find_byname ) (struct ip_fw_chain*,struct tid_info*,struct named_object**) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct obj_idx {scalar_t__ type; int /*<<< orphan*/  uidx; } ;
struct named_object {scalar_t__ subtype; int /*<<< orphan*/  kidx; int /*<<< orphan*/  refcnt; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int EINVAL ; 
 struct opcode_obj_rewrite* find_op_rw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int stub1 (struct ip_fw_chain*,struct tid_info*,struct named_object**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ref_opcode_object(struct ip_fw_chain *ch, ipfw_insn *cmd, struct tid_info *ti,
    struct obj_idx *pidx, int *unresolved)
{
	struct named_object *no;
	struct opcode_obj_rewrite *rw;
	int error;

	/* Check if this opcode is candidate for rewrite */
	rw = find_op_rw(cmd, &ti->uidx, &ti->type);
	if (rw == NULL)
		return (0);

	/* Need to rewrite. Save necessary fields */
	pidx->uidx = ti->uidx;
	pidx->type = ti->type;

	/* Try to find referenced kernel object */
	error = rw->find_byname(ch, ti, &no);
	if (error != 0)
		return (error);
	if (no == NULL) {
		/*
		 * Report about unresolved object for automaic
		 * creation.
		 */
		*unresolved = 1;
		return (0);
	}

	/*
	 * Object is already exist.
	 * Its subtype should match with expected value.
	 */
	if (ti->type != no->subtype)
		return (EINVAL);

	/* Bump refcount and update kidx. */
	no->refcnt++;
	rw->update(cmd, no->kidx);
	return (0);
}