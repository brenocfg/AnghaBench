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
struct mthca_ucontext {int /*<<< orphan*/  db_tab; int /*<<< orphan*/  uar; } ;
struct ib_srq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {TYPE_1__ ibmr; } ;
struct mthca_srq {struct ib_srq ibsrq; int /*<<< orphan*/  srqn; int /*<<< orphan*/  db_index; TYPE_2__ mr; } ;
struct mthca_create_srq {int /*<<< orphan*/  db_index; int /*<<< orphan*/  lkey; int /*<<< orphan*/  db_page; } ;
struct ib_udata {int dummy; } ;
struct ib_srq_init_attr {scalar_t__ srq_type; int /*<<< orphan*/  attr; } ;
struct ib_pd {int /*<<< orphan*/  device; TYPE_3__* uobject; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct ib_srq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_SRQT_BASIC ; 
 scalar_t__ ib_copy_from_udata (struct mthca_create_srq*,struct ib_udata*,int) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mthca_srq*) ; 
 struct mthca_srq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_alloc_srq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mthca_srq*) ; 
 int /*<<< orphan*/  mthca_free_srq (int /*<<< orphan*/ ,struct mthca_srq*) ; 
 int mthca_map_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_unmap_user_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mpd (struct ib_pd*) ; 
 struct mthca_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_srq *mthca_create_srq(struct ib_pd *pd,
				       struct ib_srq_init_attr *init_attr,
				       struct ib_udata *udata)
{
	struct mthca_create_srq ucmd;
	struct mthca_ucontext *context = NULL;
	struct mthca_srq *srq;
	int err;

	if (init_attr->srq_type != IB_SRQT_BASIC)
		return ERR_PTR(-ENOSYS);

	srq = kmalloc(sizeof *srq, GFP_KERNEL);
	if (!srq)
		return ERR_PTR(-ENOMEM);

	if (pd->uobject) {
		context = to_mucontext(pd->uobject->context);

		if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd)) {
			err = -EFAULT;
			goto err_free;
		}

		err = mthca_map_user_db(to_mdev(pd->device), &context->uar,
					context->db_tab, ucmd.db_index,
					ucmd.db_page);

		if (err)
			goto err_free;

		srq->mr.ibmr.lkey = ucmd.lkey;
		srq->db_index     = ucmd.db_index;
	}

	err = mthca_alloc_srq(to_mdev(pd->device), to_mpd(pd),
			      &init_attr->attr, srq);

	if (err && pd->uobject)
		mthca_unmap_user_db(to_mdev(pd->device), &context->uar,
				    context->db_tab, ucmd.db_index);

	if (err)
		goto err_free;

	if (context && ib_copy_to_udata(udata, &srq->srqn, sizeof (__u32))) {
		mthca_free_srq(to_mdev(pd->device), srq);
		err = -EFAULT;
		goto err_free;
	}

	return &srq->ibsrq;

err_free:
	kfree(srq);

	return ERR_PTR(err);
}