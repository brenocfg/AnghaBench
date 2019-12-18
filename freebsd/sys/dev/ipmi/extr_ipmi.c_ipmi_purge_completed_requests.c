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
struct ipmi_request {int dummy; } ;
struct ipmi_device {int /*<<< orphan*/  ipmi_requests; int /*<<< orphan*/  ipmi_completed_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ipmi_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ipmi_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_free_request (struct ipmi_request*) ; 
 int /*<<< orphan*/  ir_link ; 

__attribute__((used)) static void
ipmi_purge_completed_requests(struct ipmi_device *dev)
{
	struct ipmi_request *req;

	while (!TAILQ_EMPTY(&dev->ipmi_completed_requests)) {
		req = TAILQ_FIRST(&dev->ipmi_completed_requests);
		TAILQ_REMOVE(&dev->ipmi_completed_requests, req, ir_link);
		dev->ipmi_requests--;
		ipmi_free_request(req);
	}
}