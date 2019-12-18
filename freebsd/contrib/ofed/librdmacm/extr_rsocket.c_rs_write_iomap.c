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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  key; scalar_t__ addr; } ;
struct rsocket {int opts; int sbuf_bytes_avail; TYPE_1__ remote_iomap; int /*<<< orphan*/  sqe_avail; int /*<<< orphan*/  sseq_no; } ;
struct rs_iomap_mr {int index; } ;
struct rs_iomap {int dummy; } ;
struct ibv_sge {int dummy; } ;

/* Variables and functions */
 int RS_OPT_MSG_SEND ; 
 int /*<<< orphan*/  RS_OP_IOMAP_SGL ; 
 int /*<<< orphan*/  rs_msg_set (int /*<<< orphan*/ ,int) ; 
 int rs_post_write_msg (struct rsocket*,struct ibv_sge*,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_write_iomap(struct rsocket *rs, struct rs_iomap_mr *iomr,
			  struct ibv_sge *sgl, int nsge, int flags)
{
	uint64_t addr;

	rs->sseq_no++;
	rs->sqe_avail--;
	if (rs->opts & RS_OPT_MSG_SEND)
		rs->sqe_avail--;
	rs->sbuf_bytes_avail -= sizeof(struct rs_iomap);

	addr = rs->remote_iomap.addr + iomr->index * sizeof(struct rs_iomap);
	return rs_post_write_msg(rs, sgl, nsge, rs_msg_set(RS_OP_IOMAP_SGL, iomr->index),
				 flags, addr, rs->remote_iomap.key);
}