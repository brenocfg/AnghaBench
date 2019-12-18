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
struct device {int dummy; } ;
struct cc_req_mgr_handle {unsigned int req_queue_tail; unsigned int req_queue_head; unsigned int axi_completed; struct cc_crypto_req* req_queue; } ;
struct cc_drvdata {int irq; struct cc_req_mgr_handle* request_mgr_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  alg; scalar_t__ is_cpp; } ;
struct cc_crypto_req {int /*<<< orphan*/  user_arg; int /*<<< orphan*/  (* user_cb ) (struct device*,int /*<<< orphan*/ ,int) ;TYPE_1__ cpp; } ;

/* Variables and functions */
 int EPERM ; 
 int MAX_REQUEST_QUEUE_SIZE ; 
 int cc_cpp_int_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_pm_put_suspend (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void proc_completions(struct cc_drvdata *drvdata)
{
	struct cc_crypto_req *cc_req;
	struct device *dev = drvdata_to_dev(drvdata);
	struct cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;
	unsigned int *tail = &request_mgr_handle->req_queue_tail;
	unsigned int *head = &request_mgr_handle->req_queue_head;
	int rc;
	u32 mask;

	while (request_mgr_handle->axi_completed) {
		request_mgr_handle->axi_completed--;

		/* Dequeue request */
		if (*head == *tail) {
			/* We are supposed to handle a completion but our
			 * queue is empty. This is not normal. Return and
			 * hope for the best.
			 */
			dev_err(dev, "Request queue is empty head == tail %u\n",
				*head);
			break;
		}

		cc_req = &request_mgr_handle->req_queue[*tail];

		if (cc_req->cpp.is_cpp) {

			dev_dbg(dev, "CPP request completion slot: %d alg:%d\n",
				cc_req->cpp.slot, cc_req->cpp.alg);
			mask = cc_cpp_int_mask(cc_req->cpp.alg,
					       cc_req->cpp.slot);
			rc = (drvdata->irq & mask ? -EPERM : 0);
			dev_dbg(dev, "Got mask: %x irq: %x rc: %d\n", mask,
				drvdata->irq, rc);
		} else {
			dev_dbg(dev, "None CPP request completion\n");
			rc = 0;
		}

		if (cc_req->user_cb)
			cc_req->user_cb(dev, cc_req->user_arg, rc);
		*tail = (*tail + 1) & (MAX_REQUEST_QUEUE_SIZE - 1);
		dev_dbg(dev, "Dequeue request tail=%u\n", *tail);
		dev_dbg(dev, "Request completed. axi_completed=%d\n",
			request_mgr_handle->axi_completed);
		cc_pm_put_suspend(dev);
	}
}