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
typedef  int /*<<< orphan*/  ucmd ;
struct mlx5_ib_resize_cq {int cqe_size; int /*<<< orphan*/  buf_addr; scalar_t__ reserved1; scalar_t__ reserved0; } ;
struct mlx5_ib_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* umem; } ;
struct mlx5_ib_cq {struct ib_umem* resize_umem; TYPE_2__ buf; } ;
struct ib_umem {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct TYPE_3__ {struct ib_ucontext* context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IS_ERR (struct ib_umem*) ; 
 int PTR_ERR (struct ib_umem*) ; 
 int SIZE_MAX ; 
 int ib_copy_from_udata (struct mlx5_ib_resize_cq*,struct ib_udata*,int) ; 
 struct ib_umem* ib_umem_get (struct ib_ucontext*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_ib_cont_pages (struct ib_umem*,int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int resize_user(struct mlx5_ib_dev *dev, struct mlx5_ib_cq *cq,
		       int entries, struct ib_udata *udata, int *npas,
		       int *page_shift, int *cqe_size)
{
	struct mlx5_ib_resize_cq ucmd;
	struct ib_umem *umem;
	int err;
	int npages;
	struct ib_ucontext *context = cq->buf.umem->context;

	err = ib_copy_from_udata(&ucmd, udata, sizeof(ucmd));
	if (err)
		return err;

	if (ucmd.reserved0 || ucmd.reserved1)
		return -EINVAL;

	/* check multiplication overflow */
	if (ucmd.cqe_size && SIZE_MAX / ucmd.cqe_size <= entries - 1)
		return -EINVAL;

	umem = ib_umem_get(context, ucmd.buf_addr,
			   (size_t)ucmd.cqe_size * entries,
			   IB_ACCESS_LOCAL_WRITE, 1);
	if (IS_ERR(umem)) {
		err = PTR_ERR(umem);
		return err;
	}

	mlx5_ib_cont_pages(umem, ucmd.buf_addr, &npages, page_shift,
			   npas, NULL);

	cq->resize_umem = umem;
	*cqe_size = ucmd.cqe_size;

	return 0;
}