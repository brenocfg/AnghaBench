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
struct rbd_obj_request {TYPE_1__* img_request; } ;
struct ceph_osd_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  snapc; } ;

/* Variables and functions */
 struct ceph_osd_request* __rbd_obj_add_osd_request (struct rbd_obj_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ceph_osd_request *
rbd_obj_add_osd_request(struct rbd_obj_request *obj_req, int num_ops)
{
	return __rbd_obj_add_osd_request(obj_req, obj_req->img_request->snapc,
					 num_ops);
}