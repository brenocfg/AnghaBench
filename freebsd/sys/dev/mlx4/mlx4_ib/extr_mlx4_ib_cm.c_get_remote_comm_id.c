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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ attr_id; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct cm_sidr_generic_msg {int /*<<< orphan*/  request_id; } ;
struct cm_generic_msg {int /*<<< orphan*/  remote_comm_id; } ;

/* Variables and functions */
 scalar_t__ CM_SIDR_REP_ATTR_ID ; 
 scalar_t__ CM_SIDR_REQ_ATTR_ID ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static u32 get_remote_comm_id(struct ib_mad *mad)
{
	if (mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) {
		struct cm_sidr_generic_msg *msg =
			(struct cm_sidr_generic_msg *)mad;
		return be32_to_cpu(msg->request_id);
	} else if (mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) {
		pr_err("trying to set remote_comm_id in SIDR_REQ\n");
		return -1;
	} else {
		struct cm_generic_msg *msg = (struct cm_generic_msg *)mad;
		return be32_to_cpu(msg->remote_comm_id);
	}
}