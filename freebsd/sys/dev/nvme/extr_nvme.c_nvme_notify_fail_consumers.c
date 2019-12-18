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
typedef  size_t uint32_t ;
struct nvme_controller {int /*<<< orphan*/ ** cons_cookie; int /*<<< orphan*/  is_initialized; } ;
struct nvme_consumer {scalar_t__ id; int /*<<< orphan*/  (* fail_fn ) (void*) ;} ;

/* Variables and functions */
 scalar_t__ INVALID_CONSUMER_ID ; 
 size_t NVME_MAX_CONSUMERS ; 
 struct nvme_consumer* nvme_consumer ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void
nvme_notify_fail_consumers(struct nvme_controller *ctrlr)
{
	struct nvme_consumer	*cons;
	void			*ctrlr_cookie;
	uint32_t		i;

	/*
	 * This controller failed during initialization (i.e. IDENTIFY
	 *  command failed or timed out).  Do not notify any nvme
	 *  consumers of the failure here, since the consumer does not
	 *  even know about the controller yet.
	 */
	if (!ctrlr->is_initialized)
		return;

	for (i = 0; i < NVME_MAX_CONSUMERS; i++) {
		cons = &nvme_consumer[i];
		if (cons->id != INVALID_CONSUMER_ID &&
		    (ctrlr_cookie = ctrlr->cons_cookie[i]) != NULL) {
			ctrlr->cons_cookie[i] = NULL;
			if (cons->fail_fn != NULL)
				cons->fail_fn(ctrlr_cookie);
		}
	}
}