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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {struct scmi_clock_set_rate* buf; } ;
struct scmi_xfer {TYPE_1__ tx; } ;
struct scmi_handle {struct clock_info* clk_priv; } ;
struct scmi_clock_set_rate {void* value_high; void* value_low; void* id; void* flags; } ;
struct clock_info {scalar_t__ max_async_req; int /*<<< orphan*/  cur_async_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_RATE_SET ; 
 int CLOCK_SET_ASYNC ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_CLOCK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_do_xfer_with_response (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_clock_rate_set(const struct scmi_handle *handle, u32 clk_id,
			       u64 rate)
{
	int ret;
	u32 flags = 0;
	struct scmi_xfer *t;
	struct scmi_clock_set_rate *cfg;
	struct clock_info *ci = handle->clk_priv;

	ret = scmi_xfer_get_init(handle, CLOCK_RATE_SET, SCMI_PROTOCOL_CLOCK,
				 sizeof(*cfg), 0, &t);
	if (ret)
		return ret;

	if (ci->max_async_req &&
	    atomic_inc_return(&ci->cur_async_req) < ci->max_async_req)
		flags |= CLOCK_SET_ASYNC;

	cfg = t->tx.buf;
	cfg->flags = cpu_to_le32(flags);
	cfg->id = cpu_to_le32(clk_id);
	cfg->value_low = cpu_to_le32(rate & 0xffffffff);
	cfg->value_high = cpu_to_le32(rate >> 32);

	if (flags & CLOCK_SET_ASYNC)
		ret = scmi_do_xfer_with_response(handle, t);
	else
		ret = scmi_do_xfer(handle, t);

	if (ci->max_async_req)
		atomic_dec(&ci->cur_async_req);

	scmi_xfer_put(handle, t);
	return ret;
}