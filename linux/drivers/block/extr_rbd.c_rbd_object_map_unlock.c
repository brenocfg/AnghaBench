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
struct rbd_device {int /*<<< orphan*/  header_oloc; TYPE_2__* rbd_client; } ;
struct ceph_osd_client {int dummy; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_DEFINE_OID_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int ENOENT ; 
 int /*<<< orphan*/  RBD_LOCK_NAME ; 
 int ceph_cls_unlock (struct ceph_osd_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  oid ; 
 int /*<<< orphan*/  rbd_object_map_name (struct rbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,int) ; 

__attribute__((used)) static void rbd_object_map_unlock(struct rbd_device *rbd_dev)
{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	CEPH_DEFINE_OID_ONSTACK(oid);
	int ret;

	rbd_object_map_name(rbd_dev, CEPH_NOSNAP, &oid);

	ret = ceph_cls_unlock(osdc, &oid, &rbd_dev->header_oloc, RBD_LOCK_NAME,
			      "");
	if (ret && ret != -ENOENT)
		rbd_warn(rbd_dev, "failed to unlock object map: %d", ret);
}