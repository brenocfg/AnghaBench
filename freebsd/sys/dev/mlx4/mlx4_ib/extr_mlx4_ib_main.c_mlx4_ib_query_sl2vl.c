#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union sl2vl_tbl_to_u64 {int /*<<< orphan*/  sl64; int /*<<< orphan*/ * sl8; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ib_smp {int /*<<< orphan*/ * data; scalar_t__ attr_mod; int /*<<< orphan*/  attr_id; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_SMP_ATTR_SL_TO_VL_TABLE ; 
 int MLX4_MAD_IFC_IGNORE_KEYS ; 
 int MLX4_MAD_IFC_NET_VIEW ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_MAD_IFC (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 scalar_t__ mlx4_is_mfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_slave (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx4_ib_query_sl2vl(struct ib_device *ibdev, u8 port, u64 *sl2vl_tbl)
{
	union sl2vl_tbl_to_u64 sl2vl64;
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int mad_ifc_flags = MLX4_MAD_IFC_IGNORE_KEYS;
	int err = -ENOMEM;
	int jj;

	if (mlx4_is_slave(to_mdev(ibdev)->dev)) {
		*sl2vl_tbl = 0;
		return 0;
	}

	in_mad  = kzalloc(sizeof(*in_mad), GFP_KERNEL);
	out_mad = kmalloc(sizeof(*out_mad), GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_SL_TO_VL_TABLE;
	in_mad->attr_mod = 0;

	if (mlx4_is_mfunc(to_mdev(ibdev)->dev))
		mad_ifc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(to_mdev(ibdev), mad_ifc_flags, port, NULL, NULL,
			   in_mad, out_mad);
	if (err)
		goto out;

	for (jj = 0; jj < 8; jj++)
		sl2vl64.sl8[jj] = ((struct ib_smp *)out_mad)->data[jj];
	*sl2vl_tbl = sl2vl64.sl64;

out:
	kfree(in_mad);
	kfree(out_mad);
	return err;
}