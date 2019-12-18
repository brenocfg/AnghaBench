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
typedef  int /*<<< orphan*/  u16 ;
struct rbd_obj_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_TRUNCATE ; 
 int /*<<< orphan*/  CEPH_OSD_OP_ZERO ; 
 scalar_t__ rbd_obj_is_tail (struct rbd_obj_request*) ; 

__attribute__((used)) static u16 truncate_or_zero_opcode(struct rbd_obj_request *obj_req)
{
	return rbd_obj_is_tail(obj_req) ? CEPH_OSD_OP_TRUNCATE :
					  CEPH_OSD_OP_ZERO;
}