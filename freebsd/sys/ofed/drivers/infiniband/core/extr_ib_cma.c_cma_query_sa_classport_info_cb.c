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
struct ib_class_port_info {int dummy; } ;
struct class_port_info_context {int /*<<< orphan*/  done; int /*<<< orphan*/  class_port_info; int /*<<< orphan*/  port_num; TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ib_class_port_info*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cma_query_sa_classport_info_cb(int status,
					   struct ib_class_port_info *rec,
					   void *context)
{
	struct class_port_info_context *cb_ctx = context;

	WARN_ON(!context);

	if (status || !rec) {
		pr_debug("RDMA CM: %s port %u failed query ClassPortInfo status: %d\n",
			 cb_ctx->device->name, cb_ctx->port_num, status);
		goto out;
	}

	memcpy(cb_ctx->class_port_info, rec, sizeof(struct ib_class_port_info));

out:
	complete(&cb_ctx->done);
}