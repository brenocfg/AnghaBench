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
typedef  int /*<<< orphan*/  u8 ;
struct xfer_state {int /*<<< orphan*/  status; struct mlx5_fpga_transaction* xfer; } ;
struct mlx5_fpga_transaction {int /*<<< orphan*/  (* complete1 ) (struct mlx5_fpga_transaction const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xfer_state*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_fpga_transaction const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xfer_complete(struct xfer_state *xfer_state)
{
	const struct mlx5_fpga_transaction *xfer = xfer_state->xfer;
	u8 status = xfer_state->status;

	kfree(xfer_state);
	xfer->complete1(xfer, status);
}