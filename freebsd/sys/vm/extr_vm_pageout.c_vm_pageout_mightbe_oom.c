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
struct vm_domain {scalar_t__ vmd_oom_seq; void* vmd_oom; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_OOM_MEM ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int vm_ndomains ; 
 int /*<<< orphan*/  vm_pageout_oom (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_pageout_oom_seq ; 
 int /*<<< orphan*/  vm_pageout_oom_vote ; 

__attribute__((used)) static void
vm_pageout_mightbe_oom(struct vm_domain *vmd, int page_shortage,
    int starting_page_shortage)
{
	int old_vote;

	if (starting_page_shortage <= 0 || starting_page_shortage !=
	    page_shortage)
		vmd->vmd_oom_seq = 0;
	else
		vmd->vmd_oom_seq++;
	if (vmd->vmd_oom_seq < vm_pageout_oom_seq) {
		if (vmd->vmd_oom) {
			vmd->vmd_oom = FALSE;
			atomic_subtract_int(&vm_pageout_oom_vote, 1);
		}
		return;
	}

	/*
	 * Do not follow the call sequence until OOM condition is
	 * cleared.
	 */
	vmd->vmd_oom_seq = 0;

	if (vmd->vmd_oom)
		return;

	vmd->vmd_oom = TRUE;
	old_vote = atomic_fetchadd_int(&vm_pageout_oom_vote, 1);
	if (old_vote != vm_ndomains - 1)
		return;

	/*
	 * The current pagedaemon thread is the last in the quorum to
	 * start OOM.  Initiate the selection and signaling of the
	 * victim.
	 */
	vm_pageout_oom(VM_OOM_MEM);

	/*
	 * After one round of OOM terror, recall our vote.  On the
	 * next pass, current pagedaemon would vote again if the low
	 * memory condition is still there, due to vmd_oom being
	 * false.
	 */
	vmd->vmd_oom = FALSE;
	atomic_subtract_int(&vm_pageout_oom_vote, 1);
}