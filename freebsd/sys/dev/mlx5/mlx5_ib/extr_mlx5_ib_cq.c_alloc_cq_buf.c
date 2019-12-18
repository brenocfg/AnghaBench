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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_cq_buf {int cqe_size; int nent; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int mlx5_buf_alloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_cq_buf(struct mlx5_ib_dev *dev, struct mlx5_ib_cq_buf *buf,
			int nent, int cqe_size)
{
	int err;

	err = mlx5_buf_alloc(dev->mdev, nent * cqe_size,
	    2 * PAGE_SIZE, &buf->buf);
	if (err)
		return err;

	buf->cqe_size = cqe_size;
	buf->nent = nent;

	return 0;
}