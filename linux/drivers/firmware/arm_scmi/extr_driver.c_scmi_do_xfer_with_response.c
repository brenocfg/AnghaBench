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
struct scmi_xfer {int /*<<< orphan*/ * async_done; } ;
struct scmi_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SCMI_MAX_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  async_response ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int scmi_do_xfer_with_response(const struct scmi_handle *handle,
			       struct scmi_xfer *xfer)
{
	int ret, timeout = msecs_to_jiffies(SCMI_MAX_RESPONSE_TIMEOUT);
	DECLARE_COMPLETION_ONSTACK(async_response);

	xfer->async_done = &async_response;

	ret = scmi_do_xfer(handle, xfer);
	if (!ret && !wait_for_completion_timeout(xfer->async_done, timeout))
		ret = -ETIMEDOUT;

	xfer->async_done = NULL;
	return ret;
}