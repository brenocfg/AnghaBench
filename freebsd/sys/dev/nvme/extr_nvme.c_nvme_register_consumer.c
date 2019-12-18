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
struct nvme_consumer {int id; int /*<<< orphan*/  fail_fn; int /*<<< orphan*/  async_fn; int /*<<< orphan*/  ctrlr_fn; int /*<<< orphan*/  ns_fn; } ;
typedef  int /*<<< orphan*/  nvme_cons_ns_fn_t ;
typedef  int /*<<< orphan*/  nvme_cons_fail_fn_t ;
typedef  int /*<<< orphan*/  nvme_cons_ctrlr_fn_t ;
typedef  int /*<<< orphan*/  nvme_cons_async_fn_t ;

/* Variables and functions */
 int INVALID_CONSUMER_ID ; 
 int NVME_MAX_CONSUMERS ; 
 struct nvme_consumer* nvme_consumer ; 
 int /*<<< orphan*/  nvme_notify_new_consumer (struct nvme_consumer*) ; 
 int /*<<< orphan*/  printf (char*) ; 

struct nvme_consumer *
nvme_register_consumer(nvme_cons_ns_fn_t ns_fn, nvme_cons_ctrlr_fn_t ctrlr_fn,
		       nvme_cons_async_fn_t async_fn,
		       nvme_cons_fail_fn_t fail_fn)
{
	int i;

	/*
	 * TODO: add locking around consumer registration.
	 */
	for (i = 0; i < NVME_MAX_CONSUMERS; i++)
		if (nvme_consumer[i].id == INVALID_CONSUMER_ID) {
			nvme_consumer[i].id = i;
			nvme_consumer[i].ns_fn = ns_fn;
			nvme_consumer[i].ctrlr_fn = ctrlr_fn;
			nvme_consumer[i].async_fn = async_fn;
			nvme_consumer[i].fail_fn = fail_fn;

			nvme_notify_new_consumer(&nvme_consumer[i]);
			return (&nvme_consumer[i]);
		}

	printf("nvme(4): consumer not registered - no slots available\n");
	return (NULL);
}