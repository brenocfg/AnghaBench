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
struct skd_scsi_request {scalar_t__* cdb; } ;
struct skd_request_context {int flush_cmd; } ;

/* Variables and functions */
 scalar_t__ SYNCHRONIZE_CACHE ; 

__attribute__((used)) static void
skd_prep_zerosize_flush_cdb(struct skd_scsi_request *scsi_req,
			    struct skd_request_context *skreq)
{
	skreq->flush_cmd = 1;

	scsi_req->cdb[0] = SYNCHRONIZE_CACHE;
	scsi_req->cdb[1] = 0;
	scsi_req->cdb[2] = 0;
	scsi_req->cdb[3] = 0;
	scsi_req->cdb[4] = 0;
	scsi_req->cdb[5] = 0;
	scsi_req->cdb[6] = 0;
	scsi_req->cdb[7] = 0;
	scsi_req->cdb[8] = 0;
	scsi_req->cdb[9] = 0;
}