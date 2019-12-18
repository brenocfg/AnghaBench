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
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_revision_info {int /*<<< orphan*/  impl_ver; } ;
struct scmi_handle {struct scmi_revision_info* version; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_DISCOVER_IMPLEMENT_VERSION ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_BASE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int
scmi_base_implementation_version_get(const struct scmi_handle *handle)
{
	int ret;
	__le32 *impl_ver;
	struct scmi_xfer *t;
	struct scmi_revision_info *rev = handle->version;

	ret = scmi_xfer_get_init(handle, BASE_DISCOVER_IMPLEMENT_VERSION,
				 SCMI_PROTOCOL_BASE, 0, sizeof(*impl_ver), &t);
	if (ret)
		return ret;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		impl_ver = t->rx.buf;
		rev->impl_ver = le32_to_cpu(*impl_ver);
	}

	scmi_xfer_put(handle, t);

	return ret;
}