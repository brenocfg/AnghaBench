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
struct nvme_namespace {int /*<<< orphan*/ * cons_cookie; } ;
struct nvme_controller {void** cons_cookie; int /*<<< orphan*/  is_initialized; struct nvme_namespace* ns; } ;
struct nvme_consumer {scalar_t__ id; int /*<<< orphan*/  (* ns_fn ) (struct nvme_namespace*,void*) ;} ;

/* Variables and functions */
 scalar_t__ INVALID_CONSUMER_ID ; 
 size_t NVME_MAX_CONSUMERS ; 
 struct nvme_consumer* nvme_consumer ; 
 int /*<<< orphan*/  stub1 (struct nvme_namespace*,void*) ; 

void
nvme_notify_ns(struct nvme_controller *ctrlr, int nsid)
{
	struct nvme_consumer	*cons;
	struct nvme_namespace	*ns = &ctrlr->ns[nsid - 1];
	void			*ctrlr_cookie;
	uint32_t		i;

	if (!ctrlr->is_initialized)
		return;

	for (i = 0; i < NVME_MAX_CONSUMERS; i++) {
		cons = &nvme_consumer[i];
		if (cons->id != INVALID_CONSUMER_ID && cons->ns_fn != NULL &&
		    (ctrlr_cookie = ctrlr->cons_cookie[i]) != NULL)
			ns->cons_cookie[i] = (*cons->ns_fn)(ns, ctrlr_cookie);
	}
}