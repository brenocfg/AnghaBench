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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {scalar_t__ state; int /*<<< orphan*/  pdev; } ;
struct mlx5_cmd_msg {int dummy; } ;
typedef  int /*<<< orphan*/  mlx5_cmd_cbk_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_cmd_msg*) ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ; 
 int PTR_ERR (struct mlx5_cmd_msg*) ; 
 struct mlx5_cmd_msg* alloc_msg (struct mlx5_core_dev*,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  free_msg (struct mlx5_core_dev*,struct mlx5_cmd_msg*) ; 
 int is_manage_pages (void*) ; 
 int /*<<< orphan*/  mbox_in ; 
 int /*<<< orphan*/  mbox_out ; 
 struct mlx5_cmd_msg* mlx5_alloc_cmd_msg (struct mlx5_core_dev*,int /*<<< orphan*/  const,int) ; 
 int mlx5_cmd_invoke (struct mlx5_core_dev*,struct mlx5_cmd_msg*,int,struct mlx5_cmd_msg*,void*,int,int /*<<< orphan*/ ,void*,int,scalar_t__*,int) ; 
 int mlx5_copy_from_msg (void*,struct mlx5_cmd_msg*,int) ; 
 int mlx5_copy_to_msg (struct mlx5_cmd_msg*,void*,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_free_cmd_msg (struct mlx5_core_dev*,struct mlx5_cmd_msg*) ; 
 int mlx5_internal_err_ret_value (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  opcode ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int status_to_err (scalar_t__) ; 
 scalar_t__ syndrome ; 

__attribute__((used)) static int cmd_exec_helper(struct mlx5_core_dev *dev,
			   void *in, int in_size,
			   void *out, int out_size,
			   mlx5_cmd_cbk_t callback, void *context,
			   bool force_polling)
{
	struct mlx5_cmd_msg *inb;
	struct mlx5_cmd_msg *outb;
	int pages_queue;
	const gfp_t gfp = GFP_KERNEL;
	int err;
	u8 status = 0;
	u32 drv_synd;

	if (pci_channel_offline(dev->pdev) ||
	    dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		u16 opcode = MLX5_GET(mbox_in, in, opcode);
		err = mlx5_internal_err_ret_value(dev, opcode, &drv_synd, &status);
		MLX5_SET(mbox_out, out, status, status);
		MLX5_SET(mbox_out, out, syndrome, drv_synd);
		return err;
	}

	pages_queue = is_manage_pages(in);

	inb = alloc_msg(dev, in_size, gfp);
	if (IS_ERR(inb)) {
		err = PTR_ERR(inb);
		return err;
	}

	err = mlx5_copy_to_msg(inb, in, in_size);
	if (err) {
		mlx5_core_warn(dev, "err %d\n", err);
		goto out_in;
	}

	outb = mlx5_alloc_cmd_msg(dev, gfp, out_size);
	if (IS_ERR(outb)) {
		err = PTR_ERR(outb);
		goto out_in;
	}

	err = mlx5_cmd_invoke(dev, inb, in_size, outb, out, out_size, callback,
			      context, pages_queue, &status, force_polling);
	if (err) {
		if (err == -ETIMEDOUT)
			return err;
		goto out_out;
	}

	mlx5_core_dbg(dev, "err %d, status %d\n", err, status);
	if (status) {
		err = status_to_err(status);
		goto out_out;
	}

	if (callback)
		return err;

	err = mlx5_copy_from_msg(out, outb, out_size);

out_out:
	mlx5_free_cmd_msg(dev, outb);

out_in:
	free_msg(dev, inb);
	return err;
}