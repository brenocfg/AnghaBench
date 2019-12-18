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
struct TYPE_2__ {struct scmi_msg_reset_domain_reset* buf; } ;
struct scmi_xfer {TYPE_1__ tx; } ;
struct scmi_reset_info {struct reset_dom_info* dom_info; } ;
struct scmi_msg_reset_domain_reset {void* reset_state; void* flags; void* domain_id; } ;
struct scmi_handle {struct scmi_reset_info* reset_priv; } ;
struct reset_dom_info {scalar_t__ async_reset; } ;

/* Variables and functions */
 int ASYNCHRONOUS_RESET ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_RESET ; 
 void* cpu_to_le32 (int) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_do_xfer_with_response (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_domain_reset(const struct scmi_handle *handle, u32 domain,
			     u32 flags, u32 state)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_reset_domain_reset *dom;
	struct scmi_reset_info *pi = handle->reset_priv;
	struct reset_dom_info *rdom = pi->dom_info + domain;

	if (rdom->async_reset)
		flags |= ASYNCHRONOUS_RESET;

	ret = scmi_xfer_get_init(handle, RESET, SCMI_PROTOCOL_RESET,
				 sizeof(*dom), 0, &t);
	if (ret)
		return ret;

	dom = t->tx.buf;
	dom->domain_id = cpu_to_le32(domain);
	dom->flags = cpu_to_le32(flags);
	dom->reset_state = cpu_to_le32(state);

	if (rdom->async_reset)
		ret = scmi_do_xfer_with_response(handle, t);
	else
		ret = scmi_do_xfer(handle, t);

	scmi_xfer_put(handle, t);
	return ret;
}