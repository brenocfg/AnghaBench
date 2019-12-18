#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct mlx5_eqe_vport_change {int /*<<< orphan*/  vport_num; } ;
struct TYPE_13__ {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  func_id; } ;
struct TYPE_12__ {scalar_t__ syndrome; int /*<<< orphan*/  cqn; } ;
struct TYPE_11__ {int port; } ;
struct TYPE_10__ {int /*<<< orphan*/  vector; } ;
struct TYPE_9__ {int /*<<< orphan*/  qp_srq_n; } ;
struct TYPE_8__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_14__ {int /*<<< orphan*/  raw; struct mlx5_eqe_vport_change vport_change; TYPE_6__ req_pages; TYPE_5__ cq_err; TYPE_4__ port; TYPE_3__ cmd; TYPE_2__ qp_srq; TYPE_1__ comp; } ;
struct mlx5_eqe {int type; TYPE_7__ data; scalar_t__ sub_type; } ;
struct mlx5_eq {int /*<<< orphan*/  cons_index; scalar_t__ eqn; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int /*<<< orphan*/  (* event ) (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned long) ;int /*<<< orphan*/  state; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CMD_MODE_EVENTS ; 
#define  MLX5_DCBX_EVENT_SUBTYPE_ERROR_STATE_DCBX 160 
#define  MLX5_DCBX_EVENT_SUBTYPE_LOCAL_OPER_CHANGE 159 
#define  MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_APP_PRIORITY_CHANGE 158 
#define  MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_CHANGE 157 
 int /*<<< orphan*/  MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MLX5_DEV_EVENT_VPORT_CHANGE ; 
#define  MLX5_EVENT_TYPE_CMD 156 
#define  MLX5_EVENT_TYPE_CODING_DCBX_CHANGE_EVENT 155 
#define  MLX5_EVENT_TYPE_CODING_GENERAL_NOTIFICATION_EVENT 154 
#define  MLX5_EVENT_TYPE_CODING_PORT_MODULE_EVENT 153 
#define  MLX5_EVENT_TYPE_COMM_EST 152 
#define  MLX5_EVENT_TYPE_COMP 151 
#define  MLX5_EVENT_TYPE_CQ_ERROR 150 
#define  MLX5_EVENT_TYPE_FPGA_ERROR 149 
#define  MLX5_EVENT_TYPE_FPGA_QP_ERROR 148 
#define  MLX5_EVENT_TYPE_NIC_VPORT_CHANGE 147 
#define  MLX5_EVENT_TYPE_PAGE_REQUEST 146 
#define  MLX5_EVENT_TYPE_PATH_MIG 145 
#define  MLX5_EVENT_TYPE_PATH_MIG_FAILED 144 
#define  MLX5_EVENT_TYPE_PORT_CHANGE 143 
#define  MLX5_EVENT_TYPE_SQ_DRAINED 142 
#define  MLX5_EVENT_TYPE_SRQ_CATAS_ERROR 141 
#define  MLX5_EVENT_TYPE_SRQ_LAST_WQE 140 
#define  MLX5_EVENT_TYPE_SRQ_RQ_LIMIT 139 
#define  MLX5_EVENT_TYPE_TEMP_WARN_EVENT 138 
#define  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR 137 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 136 
#define  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR 135 
 int MLX5_NUM_SPARE_EQE ; 
#define  MLX5_PORT_CHANGE_SUBTYPE_ACTIVE 134 
#define  MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG 133 
#define  MLX5_PORT_CHANGE_SUBTYPE_DOWN 132 
#define  MLX5_PORT_CHANGE_SUBTYPE_GUID 131 
#define  MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED 130 
#define  MLX5_PORT_CHANGE_SUBTYPE_LID 129 
#define  MLX5_PORT_CHANGE_SUBTYPE_PKEY 128 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcbx_subevent (scalar_t__) ; 
 int /*<<< orphan*/  eq_update_ci (struct mlx5_eq*,int) ; 
 int eqe_type_str (int) ; 
 int /*<<< orphan*/  mlx5_cmd_comp_handler (struct mlx5_core_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,int,...) ; 
 int /*<<< orphan*/  mlx5_core_req_pages_handler (struct mlx5_core_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_cq_completion (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_cq_event (struct mlx5_core_dev*,int,int) ; 
 int /*<<< orphan*/  mlx5_fpga_event (struct mlx5_core_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_port_general_notification_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_port_module_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 int /*<<< orphan*/  mlx5_rsc_event (struct mlx5_core_dev*,int,int) ; 
 int /*<<< orphan*/  mlx5_srq_event (struct mlx5_core_dev*,int,int) ; 
 int /*<<< orphan*/  mlx5_temp_warning_event (struct mlx5_core_dev*,struct mlx5_eqe*) ; 
 struct mlx5_eqe* next_eqe_sw (struct mlx5_eq*) ; 
 int /*<<< orphan*/  port_subtype_event (scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub3 (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5_eq_int(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	struct mlx5_eqe *eqe;
	int eqes_found = 0;
	int set_ci = 0;
	u32 cqn;
	u32 rsn;
	u8 port;

	while ((eqe = next_eqe_sw(eq))) {
		/*
		 * Make sure we read EQ entry contents after we've
		 * checked the ownership bit.
		 */
		rmb();

		mlx5_core_dbg(eq->dev, "eqn %d, eqe type %s\n",
			      eq->eqn, eqe_type_str(eqe->type));
		switch (eqe->type) {
		case MLX5_EVENT_TYPE_COMP:
			cqn = be32_to_cpu(eqe->data.comp.cqn) & 0xffffff;
			mlx5_cq_completion(dev, cqn);
			break;

		case MLX5_EVENT_TYPE_PATH_MIG:
		case MLX5_EVENT_TYPE_COMM_EST:
		case MLX5_EVENT_TYPE_SQ_DRAINED:
		case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
		case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
		case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
		case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
		case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
			rsn = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
			mlx5_core_dbg(dev, "event %s(%d) arrived on resource 0x%x\n",
				      eqe_type_str(eqe->type), eqe->type, rsn);
			mlx5_rsc_event(dev, rsn, eqe->type);
			break;

		case MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
		case MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
			rsn = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
			mlx5_core_dbg(dev, "SRQ event %s(%d): srqn 0x%x\n",
				      eqe_type_str(eqe->type), eqe->type, rsn);
			mlx5_srq_event(dev, rsn, eqe->type);
			break;

		case MLX5_EVENT_TYPE_CMD:
			if (dev->state != MLX5_DEVICE_STATE_INTERNAL_ERROR) {
				mlx5_cmd_comp_handler(dev, be32_to_cpu(eqe->data.cmd.vector),
				    MLX5_CMD_MODE_EVENTS);
			}
			break;

		case MLX5_EVENT_TYPE_PORT_CHANGE:
			port = (eqe->data.port.port >> 4) & 0xf;
			switch (eqe->sub_type) {
			case MLX5_PORT_CHANGE_SUBTYPE_DOWN:
			case MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
			case MLX5_PORT_CHANGE_SUBTYPE_LID:
			case MLX5_PORT_CHANGE_SUBTYPE_PKEY:
			case MLX5_PORT_CHANGE_SUBTYPE_GUID:
			case MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG:
			case MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED:
				if (dev->event)
					dev->event(dev, port_subtype_event(eqe->sub_type),
						   (unsigned long)port);
				break;
			default:
				mlx5_core_warn(dev, "Port event with unrecognized subtype: port %d, sub_type %d\n",
					       port, eqe->sub_type);
			}
			break;

		case MLX5_EVENT_TYPE_CODING_DCBX_CHANGE_EVENT:
			port = (eqe->data.port.port >> 4) & 0xf;
			switch (eqe->sub_type) {
			case MLX5_DCBX_EVENT_SUBTYPE_ERROR_STATE_DCBX:
			case MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_CHANGE:
			case MLX5_DCBX_EVENT_SUBTYPE_LOCAL_OPER_CHANGE:
			case MLX5_DCBX_EVENT_SUBTYPE_REMOTE_CONFIG_APP_PRIORITY_CHANGE:
				if (dev->event)
					dev->event(dev,
						   dcbx_subevent(eqe->sub_type),
						   0);
				break;
			default:
				mlx5_core_warn(dev,
					       "dcbx event with unrecognized subtype: port %d, sub_type %d\n",
					       port, eqe->sub_type);
			}
			break;

		case MLX5_EVENT_TYPE_CODING_GENERAL_NOTIFICATION_EVENT:
			mlx5_port_general_notification_event(dev, eqe);
			break;

		case MLX5_EVENT_TYPE_CQ_ERROR:
			cqn = be32_to_cpu(eqe->data.cq_err.cqn) & 0xffffff;
			mlx5_core_warn(dev, "CQ error on CQN 0x%x, syndrom 0x%x\n",
				       cqn, eqe->data.cq_err.syndrome);
			mlx5_cq_event(dev, cqn, eqe->type);
			break;

		case MLX5_EVENT_TYPE_PAGE_REQUEST:
			{
				u16 func_id = be16_to_cpu(eqe->data.req_pages.func_id);
				s32 npages = be32_to_cpu(eqe->data.req_pages.num_pages);

				mlx5_core_dbg(dev, "page request for func 0x%x, npages %d\n",
					      func_id, npages);
				mlx5_core_req_pages_handler(dev, func_id, npages);
			}
			break;

		case MLX5_EVENT_TYPE_CODING_PORT_MODULE_EVENT:
			mlx5_port_module_event(dev, eqe);
			break;

		case MLX5_EVENT_TYPE_NIC_VPORT_CHANGE:
			{
				struct mlx5_eqe_vport_change *vc_eqe =
						&eqe->data.vport_change;
				u16 vport_num = be16_to_cpu(vc_eqe->vport_num);

				if (dev->event)
					dev->event(dev,
					     MLX5_DEV_EVENT_VPORT_CHANGE,
					     (unsigned long)vport_num);
			}
			break;

		case MLX5_EVENT_TYPE_FPGA_ERROR:
		case MLX5_EVENT_TYPE_FPGA_QP_ERROR:
			mlx5_fpga_event(dev, eqe->type, &eqe->data.raw);
			break;
		case MLX5_EVENT_TYPE_TEMP_WARN_EVENT:
			mlx5_temp_warning_event(dev, eqe);
			break;

		default:
			mlx5_core_warn(dev, "Unhandled event 0x%x on EQ 0x%x\n",
				       eqe->type, eq->eqn);
			break;
		}

		++eq->cons_index;
		eqes_found = 1;
		++set_ci;

		/* The HCA will think the queue has overflowed if we
		 * don't tell it we've been processing events.  We
		 * create our EQs with MLX5_NUM_SPARE_EQE extra
		 * entries, so we must update our consumer index at
		 * least that often.
		 */
		if (unlikely(set_ci >= MLX5_NUM_SPARE_EQE)) {
			eq_update_ci(eq, 0);
			set_ci = 0;
		}
	}

	eq_update_ci(eq, 1);

	return eqes_found;
}