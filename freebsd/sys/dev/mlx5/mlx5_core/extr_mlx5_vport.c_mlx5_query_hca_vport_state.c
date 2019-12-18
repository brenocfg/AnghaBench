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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vport_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_1__ hca_vport_context ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_query_hca_vport_context (struct mlx5_core_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  query_hca_vport_context_out ; 

int mlx5_query_hca_vport_state(struct mlx5_core_dev *dev, u8 *vport_state)
{
	u32 *out;
	int outlen = MLX5_ST_SZ_BYTES(query_hca_vport_context_out);
	int err;

	out = mlx5_vzalloc(outlen);
	if (!out)
		return -ENOMEM;

	err = mlx5_query_hca_vport_context(dev, 1, 0, out, outlen);
	if (err)
		goto out;

	*vport_state = MLX5_GET(query_hca_vport_context_out, out,
				hca_vport_context.vport_state);

out:
	kvfree(out);
	return err;
}