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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_pages_req {int /*<<< orphan*/  work; int /*<<< orphan*/  npages; int /*<<< orphan*/  func_id; struct mlx5_core_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_wq; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_pages_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  pages_work_handler ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_core_req_pages_handler(struct mlx5_core_dev *dev, u16 func_id,
				 s32 npages)
{
	struct mlx5_pages_req *req;

	req = kzalloc(sizeof(*req), GFP_ATOMIC);
	if (!req) {
		mlx5_core_warn(dev, "failed to allocate pages request\n");
		return;
	}

	req->dev = dev;
	req->func_id = func_id;
	req->npages = npages;
	INIT_WORK(&req->work, pages_work_handler);
	if (!queue_work(dev->priv.pg_wq, &req->work))
		mlx5_core_warn(dev, "failed to queue pages handler work\n");
}