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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct mlx4_ib_cq_buf {int /*<<< orphan*/  mtt; } ;
struct ib_umem {int /*<<< orphan*/  page_size; } ;
struct ib_ucontext {int dummy; } ;
struct TYPE_4__ {int cqe_size; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IS_ERR (struct ib_umem*) ; 
 int PTR_ERR (struct ib_umem*) ; 
 struct ib_umem* ib_umem_get (struct ib_ucontext*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_umem_page_count (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int mlx4_ib_umem_write_mtt (struct mlx4_ib_dev*,int /*<<< orphan*/ *,struct ib_umem*) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int mlx4_mtt_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_ib_get_cq_umem(struct mlx4_ib_dev *dev, struct ib_ucontext *context,
			       struct mlx4_ib_cq_buf *buf, struct ib_umem **umem,
			       u64 buf_addr, int cqe)
{
	int err;
	int cqe_size = dev->dev->caps.cqe_size;

	*umem = ib_umem_get(context, buf_addr, cqe * cqe_size,
			    IB_ACCESS_LOCAL_WRITE, 1);
	if (IS_ERR(*umem))
		return PTR_ERR(*umem);

	err = mlx4_mtt_init(dev->dev, ib_umem_page_count(*umem),
			    ilog2((*umem)->page_size), &buf->mtt);
	if (err)
		goto err_buf;

	err = mlx4_ib_umem_write_mtt(dev, &buf->mtt, *umem);
	if (err)
		goto err_mtt;

	return 0;

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &buf->mtt);

err_buf:
	ib_umem_release(*umem);

	return err;
}