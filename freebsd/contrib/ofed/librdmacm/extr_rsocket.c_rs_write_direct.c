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
typedef  scalar_t__ uint32_t ;
struct rsocket {int /*<<< orphan*/  sbuf_bytes_avail; int /*<<< orphan*/  sqe_avail; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; scalar_t__ addr; } ;
struct rs_iomap {TYPE_1__ sge; scalar_t__ offset; } ;
struct ibv_sge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_OP_WRITE ; 
 int /*<<< orphan*/  rs_msg_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int rs_post_write (struct rsocket*,struct ibv_sge*,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_write_direct(struct rsocket *rs, struct rs_iomap *iom, uint64_t offset,
			   struct ibv_sge *sgl, int nsge, uint32_t length, int flags)
{
	uint64_t addr;

	rs->sqe_avail--;
	rs->sbuf_bytes_avail -= length;

	addr = iom->sge.addr + offset - iom->offset;
	return rs_post_write(rs, sgl, nsge, rs_msg_set(RS_OP_WRITE, length),
			     flags, addr, iom->sge.key);
}