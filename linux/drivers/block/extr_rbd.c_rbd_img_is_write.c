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
struct rbd_img_request {int op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OBJ_OP_DISCARD 131 
#define  OBJ_OP_READ 130 
#define  OBJ_OP_WRITE 129 
#define  OBJ_OP_ZEROOUT 128 

__attribute__((used)) static bool rbd_img_is_write(struct rbd_img_request *img_req)
{
	switch (img_req->op_type) {
	case OBJ_OP_READ:
		return false;
	case OBJ_OP_WRITE:
	case OBJ_OP_DISCARD:
	case OBJ_OP_ZEROOUT:
		return true;
	default:
		BUG();
	}
}