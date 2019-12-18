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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_handle {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_VERSION ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

int scmi_version_get(const struct scmi_handle *handle, u8 protocol,
		     u32 *version)
{
	int ret;
	__le32 *rev_info;
	struct scmi_xfer *t;

	ret = scmi_xfer_get_init(handle, PROTOCOL_VERSION, protocol, 0,
				 sizeof(*version), &t);
	if (ret)
		return ret;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		rev_info = t->rx.buf;
		*version = le32_to_cpu(*rev_info);
	}

	scmi_xfer_put(handle, t);
	return ret;
}