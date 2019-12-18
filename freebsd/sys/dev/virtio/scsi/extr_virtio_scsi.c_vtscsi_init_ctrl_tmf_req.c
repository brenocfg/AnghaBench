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
typedef  int /*<<< orphan*/  uint32_t ;
struct virtio_scsi_ctrl_tmf_req {uintptr_t tag; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  lun; } ;
struct ccb_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_SCSI_T_TMF ; 
 int /*<<< orphan*/  vtscsi_set_request_lun (struct ccb_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtscsi_init_ctrl_tmf_req(struct ccb_hdr *ccbh, uint32_t subtype,
    uintptr_t tag, struct virtio_scsi_ctrl_tmf_req *tmf_req)
{

	vtscsi_set_request_lun(ccbh, tmf_req->lun);

	tmf_req->type = VIRTIO_SCSI_T_TMF;
	tmf_req->subtype = subtype;
	tmf_req->tag = tag;
}