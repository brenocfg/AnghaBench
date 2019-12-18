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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int u8 ;
struct mlx4_port_gid_table {TYPE_1__* gids; } ;
struct mlx4_ib_iboe {int /*<<< orphan*/  lock; struct mlx4_port_gid_table* gids; } ;
struct mlx4_ib_dev {struct mlx4_ib_iboe iboe; } ;
struct ib_gid_attr {scalar_t__ gid_type; } ;
struct ib_device {int dummy; } ;
struct gid_entry {scalar_t__ gid_type; union ib_gid const gid; } ;
struct gid_cache_context {int real_index; int refcount; } ;
struct TYPE_2__ {scalar_t__ gid_type; union ib_gid const gid; struct gid_cache_context* ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MLX4_MAX_PORTS ; 
 int MLX4_MAX_PORT_GIDS ; 
 int /*<<< orphan*/  kfree (struct gid_entry*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (union ib_gid const*,union ib_gid const*,int) ; 
 int /*<<< orphan*/  memcpy (union ib_gid const*,union ib_gid const*,int) ; 
 int mlx4_ib_update_gids (struct gid_entry*,struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  rdma_cap_roce_gid_table (struct ib_device*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 
 union ib_gid const zgid ; 

__attribute__((used)) static int mlx4_ib_add_gid(struct ib_device *device,
			   u8 port_num,
			   unsigned int index,
			   const union ib_gid *gid,
			   const struct ib_gid_attr *attr,
			   void **context)
{
	struct mlx4_ib_dev *ibdev = to_mdev(device);
	struct mlx4_ib_iboe *iboe = &ibdev->iboe;
	struct mlx4_port_gid_table   *port_gid_table;
	int free = -1, found = -1;
	int ret = 0;
	int hw_update = 0;
	int i;
	struct gid_entry *gids = NULL;

	if (!rdma_cap_roce_gid_table(device, port_num))
		return -EINVAL;

	if (port_num > MLX4_MAX_PORTS)
		return -EINVAL;

	if (!context)
		return -EINVAL;

	port_gid_table = &iboe->gids[port_num - 1];
	spin_lock_bh(&iboe->lock);
	for (i = 0; i < MLX4_MAX_PORT_GIDS; ++i) {
		if (!memcmp(&port_gid_table->gids[i].gid, gid, sizeof(*gid)) &&
		    (port_gid_table->gids[i].gid_type == attr->gid_type))  {
			found = i;
			break;
		}
		if (free < 0 && !memcmp(&port_gid_table->gids[i].gid, &zgid, sizeof(*gid)))
			free = i; /* HW has space */
	}

	if (found < 0) {
		if (free < 0) {
			ret = -ENOSPC;
		} else {
			port_gid_table->gids[free].ctx = kmalloc(sizeof(*port_gid_table->gids[free].ctx), GFP_ATOMIC);
			if (!port_gid_table->gids[free].ctx) {
				ret = -ENOMEM;
			} else {
				*context = port_gid_table->gids[free].ctx;
				memcpy(&port_gid_table->gids[free].gid, gid, sizeof(*gid));
				port_gid_table->gids[free].gid_type = attr->gid_type;
				port_gid_table->gids[free].ctx->real_index = free;
				port_gid_table->gids[free].ctx->refcount = 1;
				hw_update = 1;
			}
		}
	} else {
		struct gid_cache_context *ctx = port_gid_table->gids[found].ctx;
		*context = ctx;
		ctx->refcount++;
	}
	if (!ret && hw_update) {
		gids = kmalloc(sizeof(*gids) * MLX4_MAX_PORT_GIDS, GFP_ATOMIC);
		if (!gids) {
			ret = -ENOMEM;
		} else {
			for (i = 0; i < MLX4_MAX_PORT_GIDS; i++) {
				memcpy(&gids[i].gid, &port_gid_table->gids[i].gid, sizeof(union ib_gid));
				gids[i].gid_type = port_gid_table->gids[i].gid_type;
			}
		}
	}
	spin_unlock_bh(&iboe->lock);

	if (!ret && hw_update) {
		ret = mlx4_ib_update_gids(gids, ibdev, port_num);
		kfree(gids);
	}

	return ret;
}