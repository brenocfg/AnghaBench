#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ strong; scalar_t__ weak; int /*<<< orphan*/  desc; int /*<<< orphan*/  debug_id; } ;
struct binder_ref {TYPE_2__ data; TYPE_1__* proc; int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_cleanup_ref_olocked (struct binder_ref*) ; 
 int /*<<< orphan*/  binder_dec_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool binder_dec_ref_olocked(struct binder_ref *ref, int strong)
{
	if (strong) {
		if (ref->data.strong == 0) {
			binder_user_error("%d invalid dec strong, ref %d desc %d s %d w %d\n",
					  ref->proc->pid, ref->data.debug_id,
					  ref->data.desc, ref->data.strong,
					  ref->data.weak);
			return false;
		}
		ref->data.strong--;
		if (ref->data.strong == 0)
			binder_dec_node(ref->node, strong, 1);
	} else {
		if (ref->data.weak == 0) {
			binder_user_error("%d invalid dec weak, ref %d desc %d s %d w %d\n",
					  ref->proc->pid, ref->data.debug_id,
					  ref->data.desc, ref->data.strong,
					  ref->data.weak);
			return false;
		}
		ref->data.weak--;
	}
	if (ref->data.strong == 0 && ref->data.weak == 0) {
		binder_cleanup_ref_olocked(ref);
		return true;
	}
	return false;
}