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
typedef  int /*<<< orphan*/  u32 ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_CMD_FLUSH ; 
 int /*<<< orphan*/  NBD_CMD_READ ; 
 int /*<<< orphan*/  NBD_CMD_TRIM ; 
 int /*<<< orphan*/  NBD_CMD_WRITE ; 
#define  REQ_OP_DISCARD 131 
#define  REQ_OP_FLUSH 130 
#define  REQ_OP_READ 129 
#define  REQ_OP_WRITE 128 
 int /*<<< orphan*/  U32_MAX ; 
 int req_op (struct request*) ; 

__attribute__((used)) static u32 req_to_nbd_cmd_type(struct request *req)
{
	switch (req_op(req)) {
	case REQ_OP_DISCARD:
		return NBD_CMD_TRIM;
	case REQ_OP_FLUSH:
		return NBD_CMD_FLUSH;
	case REQ_OP_WRITE:
		return NBD_CMD_WRITE;
	case REQ_OP_READ:
		return NBD_CMD_READ;
	default:
		return U32_MAX;
	}
}