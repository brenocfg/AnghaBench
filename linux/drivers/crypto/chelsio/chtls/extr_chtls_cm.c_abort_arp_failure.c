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
struct sk_buff {int dummy; } ;
struct cpl_abort_req {int /*<<< orphan*/  cmd; } ;
struct chtls_dev {TYPE_1__* lldi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_NO_RST ; 
 struct cpl_abort_req* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void abort_arp_failure(void *handle, struct sk_buff *skb)
{
	struct cpl_abort_req *req = cplhdr(skb);
	struct chtls_dev *cdev;

	cdev = (struct chtls_dev *)handle;
	req->cmd = CPL_ABORT_NO_RST;
	cxgb4_ofld_send(cdev->lldi->ports[0], skb);
}