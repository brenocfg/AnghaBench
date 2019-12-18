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
typedef  int u32 ;
struct scsi_cmnd {TYPE_1__* device; struct request* request; } ;
struct request {int dummy; } ;
struct TYPE_2__ {int sector_size; } ;

/* Variables and functions */
 int blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 

__attribute__((used)) static bool ata_check_nblocks(struct scsi_cmnd *scmd, u32 n_blocks)
{
	struct request *rq = scmd->request;
	u32 req_blocks;

	if (!blk_rq_is_passthrough(rq))
		return true;

	req_blocks = blk_rq_bytes(rq) / scmd->device->sector_size;
	if (n_blocks > req_blocks)
		return false;

	return true;
}