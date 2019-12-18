#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_ucontext {int dummy; } ;
struct mlx5_ib_rwq {int rq_num_pas; int page_shift; int wq_sig; int /*<<< orphan*/  umem; int /*<<< orphan*/  create_type; int /*<<< orphan*/  db; int /*<<< orphan*/  buf_size; scalar_t__ log_page_size; int /*<<< orphan*/  rq_page_offset; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_ib_create_wq {int flags; int /*<<< orphan*/  db_addr; scalar_t__ buf_addr; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_ADAPTER_PAGE_SHIFT ; 
 int MLX5_WQ_FLAG_SIGNATURE ; 
 int /*<<< orphan*/  MLX5_WQ_USER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_get (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_cont_pages (int /*<<< orphan*/ ,scalar_t__,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int mlx5_ib_db_map_user (struct mlx5_ib_ucontext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,...) ; 
 int mlx5_ib_get_buf_offset (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 struct mlx5_ib_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_user_rq(struct mlx5_ib_dev *dev, struct ib_pd *pd,
			  struct mlx5_ib_rwq *rwq,
			  struct mlx5_ib_create_wq *ucmd)
{
	struct mlx5_ib_ucontext *context;
	int page_shift = 0;
	int npages;
	u32 offset = 0;
	int ncont = 0;
	int err;

	if (!ucmd->buf_addr)
		return -EINVAL;

	context = to_mucontext(pd->uobject->context);
	rwq->umem = ib_umem_get(pd->uobject->context, ucmd->buf_addr,
			       rwq->buf_size, 0, 0);
	if (IS_ERR(rwq->umem)) {
		mlx5_ib_dbg(dev, "umem_get failed\n");
		err = PTR_ERR(rwq->umem);
		return err;
	}

	mlx5_ib_cont_pages(rwq->umem, ucmd->buf_addr, &npages, &page_shift,
			   &ncont, NULL);
	err = mlx5_ib_get_buf_offset(ucmd->buf_addr, page_shift,
				     &rwq->rq_page_offset);
	if (err) {
		mlx5_ib_warn(dev, "bad offset\n");
		goto err_umem;
	}

	rwq->rq_num_pas = ncont;
	rwq->page_shift = page_shift;
	rwq->log_page_size =  page_shift - MLX5_ADAPTER_PAGE_SHIFT;
	rwq->wq_sig = !!(ucmd->flags & MLX5_WQ_FLAG_SIGNATURE);

	mlx5_ib_dbg(dev, "addr 0x%llx, size %zd, npages %d, page_shift %d, ncont %d, offset %d\n",
		    (unsigned long long)ucmd->buf_addr, rwq->buf_size,
		    npages, page_shift, ncont, offset);

	err = mlx5_ib_db_map_user(context, ucmd->db_addr, &rwq->db);
	if (err) {
		mlx5_ib_dbg(dev, "map failed\n");
		goto err_umem;
	}

	rwq->create_type = MLX5_WQ_USER;
	return 0;

err_umem:
	ib_umem_release(rwq->umem);
	return err;
}