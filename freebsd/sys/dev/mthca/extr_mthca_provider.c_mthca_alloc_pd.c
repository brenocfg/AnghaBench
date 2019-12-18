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
struct ib_pd {int dummy; } ;
struct mthca_pd {struct ib_pd ibpd; int /*<<< orphan*/  pd_num; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct ib_pd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mthca_pd*) ; 
 struct mthca_pd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_pd_alloc (int /*<<< orphan*/ ,int,struct mthca_pd*) ; 
 int /*<<< orphan*/  mthca_pd_free (int /*<<< orphan*/ ,struct mthca_pd*) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct ib_pd *mthca_alloc_pd(struct ib_device *ibdev,
				    struct ib_ucontext *context,
				    struct ib_udata *udata)
{
	struct mthca_pd *pd;
	int err;

	pd = kmalloc(sizeof *pd, GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);

	err = mthca_pd_alloc(to_mdev(ibdev), !context, pd);
	if (err) {
		kfree(pd);
		return ERR_PTR(err);
	}

	if (context) {
		if (ib_copy_to_udata(udata, &pd->pd_num, sizeof (__u32))) {
			mthca_pd_free(to_mdev(ibdev), pd);
			kfree(pd);
			return ERR_PTR(-EFAULT);
		}
	}

	return &pd->ibpd;
}