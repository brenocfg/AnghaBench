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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct nvme_completion {int cid; int /*<<< orphan*/  sqid; int /*<<< orphan*/  sqhd; int /*<<< orphan*/  cdw0; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int NVME_STATUS_GET_DNR (int) ; 
 int NVME_STATUS_GET_M (int) ; 
 int NVME_STATUS_GET_P (int) ; 
 int NVME_STATUS_GET_SC (int) ; 
 int NVME_STATUS_GET_SCT (int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int) ; 

void
nvme_dump_completion(struct nvme_completion *cpl)
{
	uint8_t p, sc, sct, m, dnr;
	uint16_t status;

	status = le16toh(cpl->status);

	p = NVME_STATUS_GET_P(status);
	sc = NVME_STATUS_GET_SC(status);
	sct = NVME_STATUS_GET_SCT(status);
	m = NVME_STATUS_GET_M(status);
	dnr = NVME_STATUS_GET_DNR(status);

	printf("cdw0:%08x sqhd:%04x sqid:%04x "
	    "cid:%04x p:%x sc:%02x sct:%x m:%x dnr:%x\n",
	    le32toh(cpl->cdw0), le16toh(cpl->sqhd), le16toh(cpl->sqid),
	    cpl->cid, p, sc, sct, m, dnr);
}