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
struct TYPE_2__ {int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {TYPE_1__ ex; } ;
struct ceph_osd_request {int /*<<< orphan*/  r_data_offset; int /*<<< orphan*/  r_mtime; int /*<<< orphan*/  r_flags; struct rbd_obj_request* r_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_FLAG_WRITE ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_osd_format_write(struct ceph_osd_request *osd_req)
{
	struct rbd_obj_request *obj_request = osd_req->r_priv;

	osd_req->r_flags = CEPH_OSD_FLAG_WRITE;
	ktime_get_real_ts64(&osd_req->r_mtime);
	osd_req->r_data_offset = obj_request->ex.oe_off;
}