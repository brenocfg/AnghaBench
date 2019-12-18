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
struct binder_ref_data {int dummy; } ;
struct binder_ref {struct binder_ref_data data; } ;
struct binder_proc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int binder_dec_ref_olocked (struct binder_ref*,int) ; 
 int /*<<< orphan*/  binder_free_ref (struct binder_ref*) ; 
 struct binder_ref* binder_get_ref_olocked (struct binder_proc*,int /*<<< orphan*/ ,int) ; 
 int binder_inc_ref_olocked (struct binder_ref*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_proc_unlock (struct binder_proc*) ; 

__attribute__((used)) static int binder_update_ref_for_handle(struct binder_proc *proc,
		uint32_t desc, bool increment, bool strong,
		struct binder_ref_data *rdata)
{
	int ret = 0;
	struct binder_ref *ref;
	bool delete_ref = false;

	binder_proc_lock(proc);
	ref = binder_get_ref_olocked(proc, desc, strong);
	if (!ref) {
		ret = -EINVAL;
		goto err_no_ref;
	}
	if (increment)
		ret = binder_inc_ref_olocked(ref, strong, NULL);
	else
		delete_ref = binder_dec_ref_olocked(ref, strong);

	if (rdata)
		*rdata = ref->data;
	binder_proc_unlock(proc);

	if (delete_ref)
		binder_free_ref(ref);
	return ret;

err_no_ref:
	binder_proc_unlock(proc);
	return ret;
}