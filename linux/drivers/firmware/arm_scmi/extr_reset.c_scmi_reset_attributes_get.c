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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_reset_info {int num_domains; } ;
struct scmi_handle {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int NUM_RESET_DOMAIN_MASK ; 
 int /*<<< orphan*/  PROTOCOL_ATTRIBUTES ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_RESET ; 
 int get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_reset_attributes_get(const struct scmi_handle *handle,
				     struct scmi_reset_info *pi)
{
	int ret;
	struct scmi_xfer *t;
	u32 attr;

	ret = scmi_xfer_get_init(handle, PROTOCOL_ATTRIBUTES,
				 SCMI_PROTOCOL_RESET, 0, sizeof(attr), &t);
	if (ret)
		return ret;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		attr = get_unaligned_le32(t->rx.buf);
		pi->num_domains = attr & NUM_RESET_DOMAIN_MASK;
	}

	scmi_xfer_put(handle, t);
	return ret;
}