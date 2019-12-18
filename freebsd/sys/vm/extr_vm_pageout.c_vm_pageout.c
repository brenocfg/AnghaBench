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
struct thread {int /*<<< orphan*/  td_name; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ VM_DOMAIN_EMPTY (int) ; 
 scalar_t__ bootverbose ; 
 struct proc* curproc ; 
 struct thread* curthread ; 
 int kthread_add (int /*<<< orphan*/  (*) (void*),void*,struct proc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,...) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  swap_pager_swap_init () ; 
 int /*<<< orphan*/  uma_reclaim_worker ; 
 int vm_ndomains ; 
 int /*<<< orphan*/  vm_oom_ratelim_mtx ; 
 int /*<<< orphan*/  vm_pageout_laundry_worker ; 
 int /*<<< orphan*/  vm_pageout_worker (void*) ; 

__attribute__((used)) static void
vm_pageout(void)
{
	struct proc *p;
	struct thread *td;
	int error, first, i;

	p = curproc;
	td = curthread;

	mtx_init(&vm_oom_ratelim_mtx, "vmoomr", NULL, MTX_DEF);
	swap_pager_swap_init();
	for (first = -1, i = 0; i < vm_ndomains; i++) {
		if (VM_DOMAIN_EMPTY(i)) {
			if (bootverbose)
				printf("domain %d empty; skipping pageout\n",
				    i);
			continue;
		}
		if (first == -1)
			first = i;
		else {
			error = kthread_add(vm_pageout_worker,
			    (void *)(uintptr_t)i, p, NULL, 0, 0, "dom%d", i);
			if (error != 0)
				panic("starting pageout for domain %d: %d\n",
				    i, error);
		}
		error = kthread_add(vm_pageout_laundry_worker,
		    (void *)(uintptr_t)i, p, NULL, 0, 0, "laundry: dom%d", i);
		if (error != 0)
			panic("starting laundry for domain %d: %d", i, error);
	}
	error = kthread_add(uma_reclaim_worker, NULL, p, NULL, 0, 0, "uma");
	if (error != 0)
		panic("starting uma_reclaim helper, error %d\n", error);

	snprintf(td->td_name, sizeof(td->td_name), "dom%d", first);
	vm_pageout_worker((void *)(uintptr_t)first);
}