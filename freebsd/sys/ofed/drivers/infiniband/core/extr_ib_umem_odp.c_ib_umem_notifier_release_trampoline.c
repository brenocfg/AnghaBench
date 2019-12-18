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
typedef  int /*<<< orphan*/  u64 ;
struct ib_umem {TYPE_2__* context; TYPE_1__* odp_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* invalidate_range ) (struct ib_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int dying; int /*<<< orphan*/  notifier_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_end (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_notifier_start_account (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_start (struct ib_umem*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  stub1 (struct ib_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_umem_notifier_release_trampoline(struct ib_umem *item, u64 start,
					       u64 end, void *cookie) {
	/*
	 * Increase the number of notifiers running, to
	 * prevent any further fault handling on this MR.
	 */
	ib_umem_notifier_start_account(item);
	item->odp_data->dying = 1;
	/* Make sure that the fact the umem is dying is out before we release
	 * all pending page faults. */
	smp_wmb();
	complete_all(&item->odp_data->notifier_completion);
	item->context->invalidate_range(item, ib_umem_start(item),
					ib_umem_end(item));
	return 0;
}