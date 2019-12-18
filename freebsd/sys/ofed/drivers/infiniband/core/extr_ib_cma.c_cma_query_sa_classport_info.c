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
struct ib_device {int /*<<< orphan*/  name; } ;
struct ib_class_port_info {int dummy; } ;
struct class_port_info_context {int /*<<< orphan*/  done; int /*<<< orphan*/  sa_query; int /*<<< orphan*/  port_num; struct ib_class_port_info* class_port_info; struct ib_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMA_QUERY_CLASSPORT_INFO_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cma_query_sa_classport_info_cb ; 
 int ib_sa_classport_info_rec_query (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct class_port_info_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct class_port_info_context*) ; 
 struct class_port_info_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_query_sa_classport_info(struct ib_device *device, u8 port_num,
				       struct ib_class_port_info *class_port_info)
{
	struct class_port_info_context *cb_ctx;
	int ret;

	cb_ctx = kmalloc(sizeof(*cb_ctx), GFP_KERNEL);
	if (!cb_ctx)
		return -ENOMEM;

	cb_ctx->device = device;
	cb_ctx->class_port_info = class_port_info;
	cb_ctx->port_num = port_num;
	init_completion(&cb_ctx->done);

	ret = ib_sa_classport_info_rec_query(&sa_client, device, port_num,
					     CMA_QUERY_CLASSPORT_INFO_TIMEOUT,
					     GFP_KERNEL, cma_query_sa_classport_info_cb,
					     cb_ctx, &cb_ctx->sa_query);
	if (ret < 0) {
		pr_err("RDMA CM: %s port %u failed to send ClassPortInfo query, ret: %d\n",
		       device->name, port_num, ret);
		goto out;
	}

	wait_for_completion(&cb_ctx->done);

out:
	kfree(cb_ctx);
	return ret;
}