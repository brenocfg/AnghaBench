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
struct rbd_obj_request {int /*<<< orphan*/  read_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBD_OBJ_READ_START ; 

__attribute__((used)) static int rbd_obj_init_read(struct rbd_obj_request *obj_req)
{
	obj_req->read_state = RBD_OBJ_READ_START;
	return 0;
}