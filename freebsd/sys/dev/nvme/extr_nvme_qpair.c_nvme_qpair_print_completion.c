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
typedef  int /*<<< orphan*/  uint16_t ;
struct nvme_qpair {int /*<<< orphan*/  ctrlr; } ;
struct nvme_completion {int /*<<< orphan*/  cdw0; int /*<<< orphan*/  cid; int /*<<< orphan*/  sqid; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_STATUS_GET_SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_STATUS_GET_SCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_status_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_qpair_print_completion(struct nvme_qpair *qpair,
    struct nvme_completion *cpl)
{
	uint16_t sct, sc;

	sct = NVME_STATUS_GET_SCT(cpl->status);
	sc = NVME_STATUS_GET_SC(cpl->status);

	nvme_printf(qpair->ctrlr, "%s (%02x/%02x) sqid:%d cid:%d cdw0:%x\n",
	    get_status_string(sct, sc), sct, sc, cpl->sqid, cpl->cid,
	    cpl->cdw0);
}