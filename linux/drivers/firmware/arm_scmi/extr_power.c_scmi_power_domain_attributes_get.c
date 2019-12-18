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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {struct scmi_msg_resp_power_domain_attributes* buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct scmi_xfer {TYPE_2__ rx; TYPE_1__ tx; } ;
struct scmi_msg_resp_power_domain_attributes {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct scmi_handle {int dummy; } ;
struct power_dom_info {int /*<<< orphan*/  name; int /*<<< orphan*/  state_set_sync; int /*<<< orphan*/  state_set_async; int /*<<< orphan*/  state_set_notify; } ;
typedef  int /*<<< orphan*/  domain ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOMAIN_ATTRIBUTES ; 
 int /*<<< orphan*/  SCMI_MAX_STR_SIZE ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_POWER ; 
 int /*<<< orphan*/  SUPPORTS_STATE_SET_ASYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUPPORTS_STATE_SET_NOTIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUPPORTS_STATE_SET_SYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scmi_power_domain_attributes_get(const struct scmi_handle *handle, u32 domain,
				 struct power_dom_info *dom_info)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_resp_power_domain_attributes *attr;

	ret = scmi_xfer_get_init(handle, POWER_DOMAIN_ATTRIBUTES,
				 SCMI_PROTOCOL_POWER, sizeof(domain),
				 sizeof(*attr), &t);
	if (ret)
		return ret;

	put_unaligned_le32(domain, t->tx.buf);
	attr = t->rx.buf;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		u32 flags = le32_to_cpu(attr->flags);

		dom_info->state_set_notify = SUPPORTS_STATE_SET_NOTIFY(flags);
		dom_info->state_set_async = SUPPORTS_STATE_SET_ASYNC(flags);
		dom_info->state_set_sync = SUPPORTS_STATE_SET_SYNC(flags);
		strlcpy(dom_info->name, attr->name, SCMI_MAX_STR_SIZE);
	}

	scmi_xfer_put(handle, t);
	return ret;
}