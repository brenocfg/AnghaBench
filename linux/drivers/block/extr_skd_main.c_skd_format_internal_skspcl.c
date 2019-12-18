#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int n_sg; int /*<<< orphan*/  sksg_dma_address; struct fit_sg_descriptor* sksg_list; } ;
struct skd_special_context {int /*<<< orphan*/  db_dma_address; TYPE_3__ req; TYPE_1__* msg_buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg_list_dma_address; } ;
struct skd_scsi_request {TYPE_2__ hdr; } ;
struct skd_device {struct skd_special_context internal_skspcl; } ;
struct fit_sg_descriptor {long long next_desc_ptr; scalar_t__ dev_side_addr; int /*<<< orphan*/  host_side_addr; scalar_t__ byte_count; int /*<<< orphan*/  control; } ;
struct fit_msg_hdr {int num_protocol_cmds_coalesced; int /*<<< orphan*/  protocol_id; } ;
struct TYPE_4__ {struct skd_scsi_request* scsi; struct fit_msg_hdr fmh; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIT_PROTOCOL_ID_SOFIT ; 
 int /*<<< orphan*/  FIT_SGD_CONTROL_LAST ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skd_scsi_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int skd_format_internal_skspcl(struct skd_device *skdev)
{
	struct skd_special_context *skspcl = &skdev->internal_skspcl;
	struct fit_sg_descriptor *sgd = &skspcl->req.sksg_list[0];
	struct fit_msg_hdr *fmh;
	uint64_t dma_address;
	struct skd_scsi_request *scsi;

	fmh = &skspcl->msg_buf->fmh;
	fmh->protocol_id = FIT_PROTOCOL_ID_SOFIT;
	fmh->num_protocol_cmds_coalesced = 1;

	scsi = &skspcl->msg_buf->scsi[0];
	memset(scsi, 0, sizeof(*scsi));
	dma_address = skspcl->req.sksg_dma_address;
	scsi->hdr.sg_list_dma_address = cpu_to_be64(dma_address);
	skspcl->req.n_sg = 1;
	sgd->control = FIT_SGD_CONTROL_LAST;
	sgd->byte_count = 0;
	sgd->host_side_addr = skspcl->db_dma_address;
	sgd->dev_side_addr = 0;
	sgd->next_desc_ptr = 0LL;

	return 1;
}