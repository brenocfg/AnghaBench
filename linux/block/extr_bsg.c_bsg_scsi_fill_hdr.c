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
struct sg_io_v4 {scalar_t__ request_len; int /*<<< orphan*/  request; scalar_t__ din_xfer_len; scalar_t__ dout_xfer_len; } ;
struct scsi_request {scalar_t__ cmd_len; int /*<<< orphan*/  cmd; } ;
struct request {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ BLK_MAX_CDB ; 
 int EFAULT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ blk_verify_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 struct scsi_request* scsi_req (struct request*) ; 
 int /*<<< orphan*/  uptr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bsg_scsi_fill_hdr(struct request *rq, struct sg_io_v4 *hdr,
		fmode_t mode)
{
	struct scsi_request *sreq = scsi_req(rq);

	if (hdr->dout_xfer_len && hdr->din_xfer_len) {
		pr_warn_once("BIDI support in bsg has been removed.\n");
		return -EOPNOTSUPP;
	}

	sreq->cmd_len = hdr->request_len;
	if (sreq->cmd_len > BLK_MAX_CDB) {
		sreq->cmd = kzalloc(sreq->cmd_len, GFP_KERNEL);
		if (!sreq->cmd)
			return -ENOMEM;
	}

	if (copy_from_user(sreq->cmd, uptr64(hdr->request), sreq->cmd_len))
		return -EFAULT;
	if (blk_verify_command(sreq->cmd, mode))
		return -EPERM;
	return 0;
}