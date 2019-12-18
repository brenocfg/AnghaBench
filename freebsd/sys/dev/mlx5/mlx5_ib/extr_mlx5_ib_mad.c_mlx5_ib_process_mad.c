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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_wc {int dummy; } ;
struct ib_mad_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ mgmt_class; scalar_t__ method; } ;
struct ib_mad {TYPE_1__ mad_hdr; int /*<<< orphan*/  data; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_FAILURE ; 
 scalar_t__ IB_MGMT_CLASS_PERF_MGMT ; 
 scalar_t__ IB_MGMT_METHOD_GET ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int process_mad (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_wc const*,struct ib_grh const*,struct ib_mad const*,struct ib_mad*) ; 
 int process_pma_cmd (struct ib_device*,int /*<<< orphan*/ ,struct ib_mad const*,struct ib_mad*) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 
 int /*<<< orphan*/  vport_counters ; 

int mlx5_ib_process_mad(struct ib_device *ibdev, int mad_flags, u8 port_num,
			const struct ib_wc *in_wc, const struct ib_grh *in_grh,
			const struct ib_mad_hdr *in, size_t in_mad_size,
			struct ib_mad_hdr *out, size_t *out_mad_size,
			u16 *out_mad_pkey_index)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);
	struct mlx5_core_dev *mdev = dev->mdev;
	const struct ib_mad *in_mad = (const struct ib_mad *)in;
	struct ib_mad *out_mad = (struct ib_mad *)out;

	if (WARN_ON_ONCE(in_mad_size != sizeof(*in_mad) ||
			 *out_mad_size != sizeof(*out_mad)))
		return IB_MAD_RESULT_FAILURE;

	memset(out_mad->data, 0, sizeof(out_mad->data));

	if (MLX5_CAP_GEN(mdev, vport_counters) &&
	    in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT &&
	    in_mad->mad_hdr.method == IB_MGMT_METHOD_GET) {
		return process_pma_cmd(ibdev, port_num, in_mad, out_mad);
	} else {
		return process_mad(ibdev, mad_flags, port_num, in_wc, in_grh,
				   in_mad, out_mad);
	}
}