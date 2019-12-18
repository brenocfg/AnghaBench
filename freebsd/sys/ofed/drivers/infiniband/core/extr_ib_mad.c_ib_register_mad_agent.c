#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ib_mad_agent {int flags; scalar_t__ hi_tid; scalar_t__ port_num; scalar_t__ qp; void* context; scalar_t__ send_handler; scalar_t__ recv_handler; struct ib_device* device; scalar_t__ rmpp_version; } ;
struct ib_mad_reg_req {int mgmt_class_version; scalar_t__ mgmt_class; struct ib_mad_agent agent; int /*<<< orphan*/  agent_list; int /*<<< orphan*/  comp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  local_work; int /*<<< orphan*/  local_list; int /*<<< orphan*/  timed_work; int /*<<< orphan*/  rmpp_list; int /*<<< orphan*/  done_list; int /*<<< orphan*/  wait_list; int /*<<< orphan*/  send_list; int /*<<< orphan*/  lock; struct ib_mad_reg_req* reg_req; TYPE_2__* qp_info; int /*<<< orphan*/  oui; } ;
struct ib_mad_port_private {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  agent_list; TYPE_1__* version; TYPE_2__* qp_info; } ;
struct ib_mad_mgmt_vendor_class_table {struct ib_mad_mgmt_vendor_class** vendor_class; } ;
struct ib_mad_mgmt_vendor_class {int dummy; } ;
struct ib_mad_mgmt_method_table {int dummy; } ;
struct ib_mad_mgmt_class_table {struct ib_mad_mgmt_method_table** method_table; } ;
struct ib_mad_agent_private {int mgmt_class_version; scalar_t__ mgmt_class; struct ib_mad_agent agent; int /*<<< orphan*/  agent_list; int /*<<< orphan*/  comp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  local_work; int /*<<< orphan*/  local_list; int /*<<< orphan*/  timed_work; int /*<<< orphan*/  rmpp_list; int /*<<< orphan*/  done_list; int /*<<< orphan*/  wait_list; int /*<<< orphan*/  send_list; int /*<<< orphan*/  lock; struct ib_mad_agent_private* reg_req; TYPE_2__* qp_info; int /*<<< orphan*/  oui; } ;
struct ib_device {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ ib_mad_send_handler ;
typedef  scalar_t__ ib_mad_recv_handler ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_4__ {scalar_t__ qp; } ;
struct TYPE_3__ {struct ib_mad_mgmt_vendor_class_table* vendor; struct ib_mad_mgmt_class_table* class; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 struct ib_mad_agent* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_MAD_USER_RMPP ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 
 scalar_t__ IB_MGMT_RMPP_VERSION ; 
 int IB_QPT_SMI ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_MGMT_CLASS ; 
 int MAX_MGMT_VERSION ; 
 int add_nonoui_reg_req (struct ib_mad_reg_req*,struct ib_mad_reg_req*,scalar_t__) ; 
 int add_oui_reg_req (struct ib_mad_reg_req*,struct ib_mad_reg_req*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ convert_mgmt_class (int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,...) ; 
 int get_spl_qp_index (int) ; 
 struct ib_mad_port_private* ib_get_mad_port (struct ib_device*,scalar_t__) ; 
 int /*<<< orphan*/  ib_is_mad_class_rmpp (int) ; 
 scalar_t__ ib_mad_client_id ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vendor_class (scalar_t__) ; 
 scalar_t__ is_vendor_method_in_use (struct ib_mad_mgmt_vendor_class*,struct ib_mad_reg_req*) ; 
 int /*<<< orphan*/  is_vendor_oui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_mad_reg_req*) ; 
 struct ib_mad_reg_req* kmemdup (struct ib_mad_reg_req*,int,int /*<<< orphan*/ ) ; 
 struct ib_mad_reg_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_completions ; 
 scalar_t__ method_in_use (struct ib_mad_mgmt_method_table**,struct ib_mad_reg_req*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timeout_sends ; 
 scalar_t__ vendor_class_index (scalar_t__) ; 

struct ib_mad_agent *ib_register_mad_agent(struct ib_device *device,
					   u8 port_num,
					   enum ib_qp_type qp_type,
					   struct ib_mad_reg_req *mad_reg_req,
					   u8 rmpp_version,
					   ib_mad_send_handler send_handler,
					   ib_mad_recv_handler recv_handler,
					   void *context,
					   u32 registration_flags)
{
	struct ib_mad_port_private *port_priv;
	struct ib_mad_agent *ret = ERR_PTR(-EINVAL);
	struct ib_mad_agent_private *mad_agent_priv;
	struct ib_mad_reg_req *reg_req = NULL;
	struct ib_mad_mgmt_class_table *class;
	struct ib_mad_mgmt_vendor_class_table *vendor;
	struct ib_mad_mgmt_vendor_class *vendor_class;
	struct ib_mad_mgmt_method_table *method;
	int ret2, qpn;
	unsigned long flags;
	u8 mgmt_class, vclass;

	/* Validate parameters */
	qpn = get_spl_qp_index(qp_type);
	if (qpn == -1) {
		dev_notice(&device->dev,
			   "ib_register_mad_agent: invalid QP Type %d\n",
			   qp_type);
		goto error1;
	}

	if (rmpp_version && rmpp_version != IB_MGMT_RMPP_VERSION) {
		dev_notice(&device->dev,
			   "ib_register_mad_agent: invalid RMPP Version %u\n",
			   rmpp_version);
		goto error1;
	}

	/* Validate MAD registration request if supplied */
	if (mad_reg_req) {
		if (mad_reg_req->mgmt_class_version >= MAX_MGMT_VERSION) {
			dev_notice(&device->dev,
				   "ib_register_mad_agent: invalid Class Version %u\n",
				   mad_reg_req->mgmt_class_version);
			goto error1;
		}
		if (!recv_handler) {
			dev_notice(&device->dev,
				   "ib_register_mad_agent: no recv_handler\n");
			goto error1;
		}
		if (mad_reg_req->mgmt_class >= MAX_MGMT_CLASS) {
			/*
			 * IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE is the only
			 * one in this range currently allowed
			 */
			if (mad_reg_req->mgmt_class !=
			    IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) {
				dev_notice(&device->dev,
					   "ib_register_mad_agent: Invalid Mgmt Class 0x%x\n",
					   mad_reg_req->mgmt_class);
				goto error1;
			}
		} else if (mad_reg_req->mgmt_class == 0) {
			/*
			 * Class 0 is reserved in IBA and is used for
			 * aliasing of IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE
			 */
			dev_notice(&device->dev,
				   "ib_register_mad_agent: Invalid Mgmt Class 0\n");
			goto error1;
		} else if (is_vendor_class(mad_reg_req->mgmt_class)) {
			/*
			 * If class is in "new" vendor range,
			 * ensure supplied OUI is not zero
			 */
			if (!is_vendor_oui(mad_reg_req->oui)) {
				dev_notice(&device->dev,
					   "ib_register_mad_agent: No OUI specified for class 0x%x\n",
					   mad_reg_req->mgmt_class);
				goto error1;
			}
		}
		/* Make sure class supplied is consistent with RMPP */
		if (!ib_is_mad_class_rmpp(mad_reg_req->mgmt_class)) {
			if (rmpp_version) {
				dev_notice(&device->dev,
					   "ib_register_mad_agent: RMPP version for non-RMPP class 0x%x\n",
					   mad_reg_req->mgmt_class);
				goto error1;
			}
		}

		/* Make sure class supplied is consistent with QP type */
		if (qp_type == IB_QPT_SMI) {
			if ((mad_reg_req->mgmt_class !=
					IB_MGMT_CLASS_SUBN_LID_ROUTED) &&
			    (mad_reg_req->mgmt_class !=
					IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)) {
				dev_notice(&device->dev,
					   "ib_register_mad_agent: Invalid SM QP type: class 0x%x\n",
					   mad_reg_req->mgmt_class);
				goto error1;
			}
		} else {
			if ((mad_reg_req->mgmt_class ==
					IB_MGMT_CLASS_SUBN_LID_ROUTED) ||
			    (mad_reg_req->mgmt_class ==
					IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)) {
				dev_notice(&device->dev,
					   "ib_register_mad_agent: Invalid GS QP type: class 0x%x\n",
					   mad_reg_req->mgmt_class);
				goto error1;
			}
		}
	} else {
		/* No registration request supplied */
		if (!send_handler)
			goto error1;
		if (registration_flags & IB_MAD_USER_RMPP)
			goto error1;
	}

	/* Validate device and port */
	port_priv = ib_get_mad_port(device, port_num);
	if (!port_priv) {
		dev_notice(&device->dev, "ib_register_mad_agent: Invalid port\n");
		ret = ERR_PTR(-ENODEV);
		goto error1;
	}

	/* Verify the QP requested is supported.  For example, Ethernet devices
	 * will not have QP0 */
	if (!port_priv->qp_info[qpn].qp) {
		dev_notice(&device->dev,
			   "ib_register_mad_agent: QP %d not supported\n", qpn);
		ret = ERR_PTR(-EPROTONOSUPPORT);
		goto error1;
	}

	/* Allocate structures */
	mad_agent_priv = kzalloc(sizeof *mad_agent_priv, GFP_KERNEL);
	if (!mad_agent_priv) {
		ret = ERR_PTR(-ENOMEM);
		goto error1;
	}

	if (mad_reg_req) {
		reg_req = kmemdup(mad_reg_req, sizeof *reg_req, GFP_KERNEL);
		if (!reg_req) {
			ret = ERR_PTR(-ENOMEM);
			goto error3;
		}
	}

	/* Now, fill in the various structures */
	mad_agent_priv->qp_info = &port_priv->qp_info[qpn];
	mad_agent_priv->reg_req = reg_req;
	mad_agent_priv->agent.rmpp_version = rmpp_version;
	mad_agent_priv->agent.device = device;
	mad_agent_priv->agent.recv_handler = recv_handler;
	mad_agent_priv->agent.send_handler = send_handler;
	mad_agent_priv->agent.context = context;
	mad_agent_priv->agent.qp = port_priv->qp_info[qpn].qp;
	mad_agent_priv->agent.port_num = port_num;
	mad_agent_priv->agent.flags = registration_flags;
	spin_lock_init(&mad_agent_priv->lock);
	INIT_LIST_HEAD(&mad_agent_priv->send_list);
	INIT_LIST_HEAD(&mad_agent_priv->wait_list);
	INIT_LIST_HEAD(&mad_agent_priv->done_list);
	INIT_LIST_HEAD(&mad_agent_priv->rmpp_list);
	INIT_DELAYED_WORK(&mad_agent_priv->timed_work, timeout_sends);
	INIT_LIST_HEAD(&mad_agent_priv->local_list);
	INIT_WORK(&mad_agent_priv->local_work, local_completions);
	atomic_set(&mad_agent_priv->refcount, 1);
	init_completion(&mad_agent_priv->comp);

	spin_lock_irqsave(&port_priv->reg_lock, flags);
	mad_agent_priv->agent.hi_tid = ++ib_mad_client_id;

	/*
	 * Make sure MAD registration (if supplied)
	 * is non overlapping with any existing ones
	 */
	if (mad_reg_req) {
		mgmt_class = convert_mgmt_class(mad_reg_req->mgmt_class);
		if (!is_vendor_class(mgmt_class)) {
			class = port_priv->version[mad_reg_req->
						   mgmt_class_version].class;
			if (class) {
				method = class->method_table[mgmt_class];
				if (method) {
					if (method_in_use(&method,
							   mad_reg_req))
						goto error4;
				}
			}
			ret2 = add_nonoui_reg_req(mad_reg_req, mad_agent_priv,
						  mgmt_class);
		} else {
			/* "New" vendor class range */
			vendor = port_priv->version[mad_reg_req->
						    mgmt_class_version].vendor;
			if (vendor) {
				vclass = vendor_class_index(mgmt_class);
				vendor_class = vendor->vendor_class[vclass];
				if (vendor_class) {
					if (is_vendor_method_in_use(
							vendor_class,
							mad_reg_req))
						goto error4;
				}
			}
			ret2 = add_oui_reg_req(mad_reg_req, mad_agent_priv);
		}
		if (ret2) {
			ret = ERR_PTR(ret2);
			goto error4;
		}
	}

	/* Add mad agent into port's agent list */
	list_add_tail(&mad_agent_priv->agent_list, &port_priv->agent_list);
	spin_unlock_irqrestore(&port_priv->reg_lock, flags);

	return &mad_agent_priv->agent;

error4:
	spin_unlock_irqrestore(&port_priv->reg_lock, flags);
	kfree(reg_req);
error3:
	kfree(mad_agent_priv);
error1:
	return ret;
}