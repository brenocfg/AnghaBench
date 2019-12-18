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
struct TYPE_4__ {int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  retries; } ;
struct ib_mad_send_wr_private {TYPE_1__* mad_agent_priv; int /*<<< orphan*/  agent_list; int /*<<< orphan*/  refcount; TYPE_2__ send_buf; int /*<<< orphan*/  timeout; int /*<<< orphan*/  retries_left; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_list; int /*<<< orphan*/  agent; } ;

/* Variables and functions */
 int ECOMM ; 
 int ETIMEDOUT ; 
#define  IB_RMPP_RESULT_CONSUMED 129 
#define  IB_RMPP_RESULT_UNHANDLED 128 
 scalar_t__ ib_mad_kernel_rmpp_agent (int /*<<< orphan*/ *) ; 
 int ib_retry_rmpp (struct ib_mad_send_wr_private*) ; 
 int ib_send_mad (struct ib_mad_send_wr_private*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retry_send(struct ib_mad_send_wr_private *mad_send_wr)
{
	int ret;

	if (!mad_send_wr->retries_left)
		return -ETIMEDOUT;

	mad_send_wr->retries_left--;
	mad_send_wr->send_buf.retries++;

	mad_send_wr->timeout = msecs_to_jiffies(mad_send_wr->send_buf.timeout_ms);

	if (ib_mad_kernel_rmpp_agent(&mad_send_wr->mad_agent_priv->agent)) {
		ret = ib_retry_rmpp(mad_send_wr);
		switch (ret) {
		case IB_RMPP_RESULT_UNHANDLED:
			ret = ib_send_mad(mad_send_wr);
			break;
		case IB_RMPP_RESULT_CONSUMED:
			ret = 0;
			break;
		default:
			ret = -ECOMM;
			break;
		}
	} else
		ret = ib_send_mad(mad_send_wr);

	if (!ret) {
		mad_send_wr->refcount++;
		list_add_tail(&mad_send_wr->agent_list,
			      &mad_send_wr->mad_agent_priv->send_list);
	}
	return ret;
}