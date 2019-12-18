#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ib_smp {int* data; void* attr_mod; int /*<<< orphan*/  attr_id; } ;
struct ib_port_attr {int lmc; int sm_sl; int state; int phys_state; int port_cap_flags; int gid_tbl_len; int active_width; int active_speed; int max_mtu; int active_mtu; int subnet_timeout; int max_vl_num; int init_type_reply; void* qkey_viol_cntr; void* bad_pkey_cntr; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  max_msg_sz; void* sm_lid; void* lid; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_5__ {int* gid_table_len; int /*<<< orphan*/ * pkey_table_len; int /*<<< orphan*/  max_msg_sz; } ;
struct TYPE_7__ {TYPE_1__ caps; } ;
struct TYPE_6__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_PORT_DOWN ; 
 int IB_PORT_EXTENDED_SPEEDS_SUP ; 
 int /*<<< orphan*/  IB_SMP_ATTR_PORT_INFO ; 
 int IB_SPEED_EDR ; 
 int IB_SPEED_FDR ; 
 int IB_SPEED_FDR10 ; 
 int IB_SPEED_QDR ; 
 int IB_SPEED_SDR ; 
 int /*<<< orphan*/  MLX4_ATTR_EXTENDED_PORT_INFO ; 
 int MLX4_MAD_IFC_IGNORE_KEYS ; 
 int MLX4_MAD_IFC_NET_VIEW ; 
 void* be16_to_cpup (int /*<<< orphan*/ *) ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 void* cpu_to_be32 (size_t) ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_MAD_IFC (TYPE_2__*,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 scalar_t__ mlx4_is_mfunc (TYPE_3__*) ; 
 TYPE_2__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int ib_link_query_port(struct ib_device *ibdev, u8 port,
			      struct ib_port_attr *props, int netw_view)
{
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int ext_active_speed;
	int mad_ifc_flags = MLX4_MAD_IFC_IGNORE_KEYS;
	int err = -ENOMEM;

	in_mad  = kzalloc(sizeof *in_mad, GFP_KERNEL);
	out_mad = kmalloc(sizeof *out_mad, GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	if (mlx4_is_mfunc(to_mdev(ibdev)->dev) && netw_view)
		mad_ifc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(to_mdev(ibdev), mad_ifc_flags, port, NULL, NULL,
				in_mad, out_mad);
	if (err)
		goto out;


	props->lid		= be16_to_cpup((__be16 *) (out_mad->data + 16));
	props->lmc		= out_mad->data[34] & 0x7;
	props->sm_lid		= be16_to_cpup((__be16 *) (out_mad->data + 18));
	props->sm_sl		= out_mad->data[36] & 0xf;
	props->state		= out_mad->data[32] & 0xf;
	props->phys_state	= out_mad->data[33] >> 4;
	props->port_cap_flags	= be32_to_cpup((__be32 *) (out_mad->data + 20));
	if (netw_view)
		props->gid_tbl_len = out_mad->data[50];
	else
		props->gid_tbl_len = to_mdev(ibdev)->dev->caps.gid_table_len[port];
	props->max_msg_sz	= to_mdev(ibdev)->dev->caps.max_msg_sz;
	props->pkey_tbl_len	= to_mdev(ibdev)->dev->caps.pkey_table_len[port];
	props->bad_pkey_cntr	= be16_to_cpup((__be16 *) (out_mad->data + 46));
	props->qkey_viol_cntr	= be16_to_cpup((__be16 *) (out_mad->data + 48));
	props->active_width	= out_mad->data[31] & 0xf;
	props->active_speed	= out_mad->data[35] >> 4;
	props->max_mtu		= out_mad->data[41] & 0xf;
	props->active_mtu	= out_mad->data[36] >> 4;
	props->subnet_timeout	= out_mad->data[51] & 0x1f;
	props->max_vl_num	= out_mad->data[37] >> 4;
	props->init_type_reply	= out_mad->data[41] >> 4;

	/* Check if extended speeds (EDR/FDR/...) are supported */
	if (props->port_cap_flags & IB_PORT_EXTENDED_SPEEDS_SUP) {
		ext_active_speed = out_mad->data[62] >> 4;

		switch (ext_active_speed) {
		case 1:
			props->active_speed = IB_SPEED_FDR;
			break;
		case 2:
			props->active_speed = IB_SPEED_EDR;
			break;
		}
	}

	/* If reported active speed is QDR, check if is FDR-10 */
	if (props->active_speed == IB_SPEED_QDR) {
		init_query_mad(in_mad);
		in_mad->attr_id = MLX4_ATTR_EXTENDED_PORT_INFO;
		in_mad->attr_mod = cpu_to_be32(port);

		err = mlx4_MAD_IFC(to_mdev(ibdev), mad_ifc_flags, port,
				   NULL, NULL, in_mad, out_mad);
		if (err)
			goto out;

		/* Checking LinkSpeedActive for FDR-10 */
		if (out_mad->data[15] & 0x1)
			props->active_speed = IB_SPEED_FDR10;
	}

	/* Avoid wrong speed value returned by FW if the IB link is down. */
	if (props->state == IB_PORT_DOWN)
		 props->active_speed = IB_SPEED_SDR;

out:
	kfree(in_mad);
	kfree(out_mad);
	return err;
}