#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mthca_ucontext {int /*<<< orphan*/  db_tab; int /*<<< orphan*/  uar; } ;
struct ib_srq {int /*<<< orphan*/  device; TYPE_1__* uobject; } ;
struct TYPE_5__ {int /*<<< orphan*/  db_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_srq*) ; 
 int /*<<< orphan*/  mthca_free_srq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mthca_unmap_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_msrq (struct ib_srq*) ; 
 struct mthca_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_destroy_srq(struct ib_srq *srq)
{
	struct mthca_ucontext *context;

	if (srq->uobject) {
		context = to_mucontext(srq->uobject->context);

		mthca_unmap_user_db(to_mdev(srq->device), &context->uar,
				    context->db_tab, to_msrq(srq)->db_index);
	}

	mthca_free_srq(to_mdev(srq->device), to_msrq(srq));
	kfree(srq);

	return 0;
}