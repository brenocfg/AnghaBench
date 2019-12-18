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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/ * data; int /*<<< orphan*/  direction; TYPE_1__* conn; int /*<<< orphan*/  complete1; scalar_t__ addr; } ;
struct xfer_transaction {TYPE_3__ transaction; struct xfer_state* xfer_state; } ;
struct xfer_state {scalar_t__ pos; scalar_t__ status; int /*<<< orphan*/  budget; int /*<<< orphan*/  inflight_count; int /*<<< orphan*/  error_count; int /*<<< orphan*/  done_count; int /*<<< orphan*/  start_count; TYPE_2__* xfer; } ;
struct TYPE_5__ {scalar_t__ addr; size_t size; TYPE_1__* conn; int /*<<< orphan*/  direction; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/  fdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IB_WC_GENERAL_ERR ; 
 scalar_t__ IB_WC_SUCCESS ; 
 size_t MLX5_FPGA_TRANSACTION_MAX_SIZE ; 
 int MLX5_FPGA_TRANSACTION_SEND_PAGE_BITS ; 
 int /*<<< orphan*/  kfree (struct xfer_transaction*) ; 
 struct xfer_transaction* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_fpga_ddr_base_get (int /*<<< orphan*/ ) ; 
 int mlx5_fpga_trans_exec (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trans_complete ; 

__attribute__((used)) static int exec_more(struct xfer_state *xfer_state)
{
	struct xfer_transaction *xfer_trans;
	size_t left, cur_size, page_size;
	u64 pos_addr, ddr_base;
	u8 *pos_data;
	int ret = 0;

	ddr_base = mlx5_fpga_ddr_base_get(xfer_state->xfer->conn->fdev);
	page_size = (xfer_state->xfer->addr + xfer_state->pos < ddr_base) ?
		    sizeof(u32) : (1 << MLX5_FPGA_TRANSACTION_SEND_PAGE_BITS);

	do {
		if (xfer_state->status != IB_WC_SUCCESS) {
			ret = -EIO;
			break;
		}

		left = xfer_state->xfer->size - xfer_state->pos;
		if (!left)
			break;

		xfer_trans = kzalloc(sizeof(*xfer_trans), GFP_ATOMIC);
		if (!xfer_trans) {
			ret = -ENOMEM;
			break;
		}

		pos_addr = xfer_state->xfer->addr + xfer_state->pos;
		pos_data = xfer_state->xfer->data + xfer_state->pos;

		/* Determine largest possible transaction at this point */
		cur_size = page_size - (pos_addr & (page_size - 1));
		if (cur_size > MLX5_FPGA_TRANSACTION_MAX_SIZE)
			cur_size = MLX5_FPGA_TRANSACTION_MAX_SIZE;
		if (cur_size > left)
			cur_size = left;

		xfer_trans->xfer_state = xfer_state;
		xfer_trans->transaction.addr = pos_addr;
		xfer_trans->transaction.complete1 = trans_complete;
		xfer_trans->transaction.conn = xfer_state->xfer->conn;
		xfer_trans->transaction.data = pos_data;
		xfer_trans->transaction.direction = xfer_state->xfer->direction;
		xfer_trans->transaction.size = cur_size;

		xfer_state->start_count++;
		xfer_state->inflight_count++;
		mlx5_fpga_dbg(xfer_state->xfer->conn->fdev, "Starting %zu bytes at %p done; %u started %u inflight %u done %u error\n",
			      xfer_trans->transaction.size,
			      xfer_trans->transaction.data,
			      xfer_state->start_count,
			      xfer_state->inflight_count,
			      xfer_state->done_count,
			      xfer_state->error_count);
		ret = mlx5_fpga_trans_exec(&xfer_trans->transaction);
		if (ret) {
			xfer_state->start_count--;
			xfer_state->inflight_count--;
			if (ret == -EBUSY)
				ret = 0;

			if (ret) {
				mlx5_fpga_warn(xfer_state->xfer->conn->fdev, "Transfer failed to start transaction: %d. %u started %u done %u error\n",
					       ret, xfer_state->start_count,
					       xfer_state->done_count,
					       xfer_state->error_count);
				xfer_state->status = IB_WC_GENERAL_ERR;
			}
			kfree(xfer_trans);
			break;
		}
		xfer_state->pos += cur_size;
		if (xfer_state->inflight_count >= xfer_state->budget)
			break;
	} while (cur_size != left);

	return ret;
}