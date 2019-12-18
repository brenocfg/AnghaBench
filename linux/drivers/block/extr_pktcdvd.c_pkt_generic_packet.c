#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int timeout; int /*<<< orphan*/  q; int /*<<< orphan*/  rq_flags; } ;
struct pktcdvd_device {TYPE_2__* bdev; } ;
struct packet_command {scalar_t__ data_direction; scalar_t__ quiet; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_disk; } ;
struct TYPE_3__ {scalar_t__ result; int /*<<< orphan*/  cmd; int /*<<< orphan*/  cmd_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDROM_PACKET_SIZE ; 
 scalar_t__ CGC_DATA_WRITE ; 
 int /*<<< orphan*/  COMMAND_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_SCSI_IN ; 
 int /*<<< orphan*/  REQ_OP_SCSI_OUT ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 struct request_queue* bdev_get_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_kern (struct request_queue*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static int pkt_generic_packet(struct pktcdvd_device *pd, struct packet_command *cgc)
{
	struct request_queue *q = bdev_get_queue(pd->bdev);
	struct request *rq;
	int ret = 0;

	rq = blk_get_request(q, (cgc->data_direction == CGC_DATA_WRITE) ?
			     REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	if (cgc->buflen) {
		ret = blk_rq_map_kern(q, rq, cgc->buffer, cgc->buflen,
				      GFP_NOIO);
		if (ret)
			goto out;
	}

	scsi_req(rq)->cmd_len = COMMAND_SIZE(cgc->cmd[0]);
	memcpy(scsi_req(rq)->cmd, cgc->cmd, CDROM_PACKET_SIZE);

	rq->timeout = 60*HZ;
	if (cgc->quiet)
		rq->rq_flags |= RQF_QUIET;

	blk_execute_rq(rq->q, pd->bdev->bd_disk, rq, 0);
	if (scsi_req(rq)->result)
		ret = -EIO;
out:
	blk_put_request(rq);
	return ret;
}