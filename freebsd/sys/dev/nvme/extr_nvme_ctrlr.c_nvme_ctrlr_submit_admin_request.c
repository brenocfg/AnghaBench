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
struct nvme_request {int dummy; } ;
struct nvme_controller {int /*<<< orphan*/  adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_qpair_submit_request (int /*<<< orphan*/ *,struct nvme_request*) ; 

void
nvme_ctrlr_submit_admin_request(struct nvme_controller *ctrlr,
    struct nvme_request *req)
{

	nvme_qpair_submit_request(&ctrlr->adminq, req);
}