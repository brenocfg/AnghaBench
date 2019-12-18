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
struct request {int dummy; } ;
struct loop_device {int lo_offset; int /*<<< orphan*/  transfer; } ;
struct loop_cmd {int /*<<< orphan*/  use_aio; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  READ ; 
#define  REQ_OP_DISCARD 132 
#define  REQ_OP_FLUSH 131 
#define  REQ_OP_READ 130 
#define  REQ_OP_WRITE 129 
#define  REQ_OP_WRITE_ZEROES 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE ; 
 struct loop_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int lo_discard (struct loop_device*,struct request*,int) ; 
 int lo_read_simple (struct loop_device*,struct request*,int) ; 
 int lo_read_transfer (struct loop_device*,struct request*,int) ; 
 int lo_req_flush (struct loop_device*,struct request*) ; 
 int lo_rw_aio (struct loop_device*,struct loop_cmd*,int,int /*<<< orphan*/ ) ; 
 int lo_write_simple (struct loop_device*,struct request*,int) ; 
 int lo_write_transfer (struct loop_device*,struct request*,int) ; 
 int req_op (struct request*) ; 

__attribute__((used)) static int do_req_filebacked(struct loop_device *lo, struct request *rq)
{
	struct loop_cmd *cmd = blk_mq_rq_to_pdu(rq);
	loff_t pos = ((loff_t) blk_rq_pos(rq) << 9) + lo->lo_offset;

	/*
	 * lo_write_simple and lo_read_simple should have been covered
	 * by io submit style function like lo_rw_aio(), one blocker
	 * is that lo_read_simple() need to call flush_dcache_page after
	 * the page is written from kernel, and it isn't easy to handle
	 * this in io submit style function which submits all segments
	 * of the req at one time. And direct read IO doesn't need to
	 * run flush_dcache_page().
	 */
	switch (req_op(rq)) {
	case REQ_OP_FLUSH:
		return lo_req_flush(lo, rq);
	case REQ_OP_DISCARD:
	case REQ_OP_WRITE_ZEROES:
		return lo_discard(lo, rq, pos);
	case REQ_OP_WRITE:
		if (lo->transfer)
			return lo_write_transfer(lo, rq, pos);
		else if (cmd->use_aio)
			return lo_rw_aio(lo, cmd, pos, WRITE);
		else
			return lo_write_simple(lo, rq, pos);
	case REQ_OP_READ:
		if (lo->transfer)
			return lo_read_transfer(lo, rq, pos);
		else if (cmd->use_aio)
			return lo_rw_aio(lo, cmd, pos, READ);
		else
			return lo_read_simple(lo, rq, pos);
	default:
		WARN_ON_ONCE(1);
		return -EIO;
	}
}