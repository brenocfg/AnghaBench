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
struct pd_req {int (* func ) (int /*<<< orphan*/ ) ;} ;
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
 struct pd_req* blk_mq_rq_to_pdu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_current ; 
 int /*<<< orphan*/  pd_req ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum action pd_special(void)
{
	struct pd_req *req = blk_mq_rq_to_pdu(pd_req);

	return req->func(pd_current);
}