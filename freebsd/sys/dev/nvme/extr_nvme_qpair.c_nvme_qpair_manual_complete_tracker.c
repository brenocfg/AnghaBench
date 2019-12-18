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
typedef  int uint32_t ;
struct nvme_tracker {int /*<<< orphan*/  cid; } ;
struct nvme_qpair {int /*<<< orphan*/  id; } ;
struct nvme_completion {int status; int /*<<< orphan*/  cid; int /*<<< orphan*/  sqid; } ;
typedef  int /*<<< orphan*/  error_print_t ;
typedef  int /*<<< orphan*/  cpl ;

/* Variables and functions */
 int NVME_STATUS_DNR_MASK ; 
 int NVME_STATUS_DNR_SHIFT ; 
 int NVME_STATUS_SCT_MASK ; 
 int NVME_STATUS_SCT_SHIFT ; 
 int NVME_STATUS_SC_MASK ; 
 int NVME_STATUS_SC_SHIFT ; 
 int /*<<< orphan*/  memset (struct nvme_completion*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_qpair_complete_tracker (struct nvme_qpair*,struct nvme_tracker*,struct nvme_completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_qpair_manual_complete_tracker(struct nvme_qpair *qpair,
    struct nvme_tracker *tr, uint32_t sct, uint32_t sc, uint32_t dnr,
    error_print_t print_on_error)
{
	struct nvme_completion	cpl;

	memset(&cpl, 0, sizeof(cpl));
	cpl.sqid = qpair->id;
	cpl.cid = tr->cid;
	cpl.status |= (sct & NVME_STATUS_SCT_MASK) << NVME_STATUS_SCT_SHIFT;
	cpl.status |= (sc & NVME_STATUS_SC_MASK) << NVME_STATUS_SC_SHIFT;
	cpl.status |= (dnr & NVME_STATUS_DNR_MASK) << NVME_STATUS_DNR_SHIFT;
	nvme_qpair_complete_tracker(qpair, tr, &cpl, print_on_error);
}