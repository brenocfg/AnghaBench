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
typedef  int uintmax_t ;
typedef  scalar_t__ u64 ;
struct xfer_state {int budget; scalar_t__ start_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; struct mlx5_fpga_transaction const* xfer; } ;
struct mlx5_fpga_transaction {scalar_t__ addr; scalar_t__ size; TYPE_1__* conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  fdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int MLX5_FPGA_TRANSACTION_SEND_ALIGN_BITS ; 
 int exec_more (struct xfer_state*) ; 
 struct xfer_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_fpga_ddr_base_get (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_fpga_ddr_size_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xfer_complete (struct xfer_state*) ; 

int mlx5_fpga_xfer_exec(const struct mlx5_fpga_transaction *xfer)
{
	u64 base = mlx5_fpga_ddr_base_get(xfer->conn->fdev);
	u64 size = mlx5_fpga_ddr_size_get(xfer->conn->fdev);
	struct xfer_state *xfer_state;
	unsigned long flags;
	bool done = false;
	int ret = 0;

	if (xfer->addr + xfer->size > base + size) {
		mlx5_fpga_warn(xfer->conn->fdev, "Transfer ends at %jx outside of DDR range %jx\n",
			       (uintmax_t)(xfer->addr + xfer->size), (uintmax_t)(base + size));
		return -EINVAL;
	}

	if (xfer->addr & MLX5_FPGA_TRANSACTION_SEND_ALIGN_BITS) {
		mlx5_fpga_warn(xfer->conn->fdev, "Transfer address %jx not aligned\n",
			       (uintmax_t)xfer->addr);
		return -EINVAL;
	}

	if (xfer->size & MLX5_FPGA_TRANSACTION_SEND_ALIGN_BITS) {
		mlx5_fpga_warn(xfer->conn->fdev, "Transfer size %zu not aligned\n",
			       xfer->size);
		return -EINVAL;
	}

	if (xfer->size < 1) {
		mlx5_fpga_warn(xfer->conn->fdev, "Empty transfer size %zu not allowed\n",
			       xfer->size);
		return -EINVAL;
	}

	xfer_state = kzalloc(sizeof(*xfer_state), GFP_KERNEL);
	xfer_state->xfer = xfer;
	xfer_state->status = IB_WC_SUCCESS;
	xfer_state->budget = 7;
	spin_lock_init(&xfer_state->lock);
	spin_lock_irqsave(&xfer_state->lock, flags);

	ret = exec_more(xfer_state);
	if (ret && (xfer_state->start_count == 0))
		done = true;

	spin_unlock_irqrestore(&xfer_state->lock, flags);

	if (done)
		xfer_complete(xfer_state);
	return ret;
}