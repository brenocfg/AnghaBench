#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct rbd_device {int /*<<< orphan*/  header_oloc; TYPE_2__* rbd_client; } ;
struct ceph_osd_client {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  cookie; } ;
struct ceph_locker {TYPE_3__ id; } ;
struct TYPE_5__ {TYPE_1__* client; } ;
struct TYPE_4__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CLS_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  CEPH_DEFINE_OID_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOENT ; 
 int ENTITY_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBD_LOCK_NAME ; 
 int ceph_cls_break_lock (struct ceph_osd_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ceph_cls_lock (struct ceph_osd_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int ceph_cls_lock_info (struct ceph_osd_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,struct ceph_locker**,scalar_t__*) ; 
 int /*<<< orphan*/  ceph_free_lockers (struct ceph_locker*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  oid ; 
 int /*<<< orphan*/  rbd_object_map_name (struct rbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,int) ; 

__attribute__((used)) static int rbd_object_map_lock(struct rbd_device *rbd_dev)
{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	CEPH_DEFINE_OID_ONSTACK(oid);
	u8 lock_type;
	char *lock_tag;
	struct ceph_locker *lockers;
	u32 num_lockers;
	bool broke_lock = false;
	int ret;

	rbd_object_map_name(rbd_dev, CEPH_NOSNAP, &oid);

again:
	ret = ceph_cls_lock(osdc, &oid, &rbd_dev->header_oloc, RBD_LOCK_NAME,
			    CEPH_CLS_LOCK_EXCLUSIVE, "", "", "", 0);
	if (ret != -EBUSY || broke_lock) {
		if (ret == -EEXIST)
			ret = 0; /* already locked by myself */
		if (ret)
			rbd_warn(rbd_dev, "failed to lock object map: %d", ret);
		return ret;
	}

	ret = ceph_cls_lock_info(osdc, &oid, &rbd_dev->header_oloc,
				 RBD_LOCK_NAME, &lock_type, &lock_tag,
				 &lockers, &num_lockers);
	if (ret) {
		if (ret == -ENOENT)
			goto again;

		rbd_warn(rbd_dev, "failed to get object map lockers: %d", ret);
		return ret;
	}

	kfree(lock_tag);
	if (num_lockers == 0)
		goto again;

	rbd_warn(rbd_dev, "breaking object map lock owned by %s%llu",
		 ENTITY_NAME(lockers[0].id.name));

	ret = ceph_cls_break_lock(osdc, &oid, &rbd_dev->header_oloc,
				  RBD_LOCK_NAME, lockers[0].id.cookie,
				  &lockers[0].id.name);
	ceph_free_lockers(lockers, num_lockers);
	if (ret) {
		if (ret == -ENOENT)
			goto again;

		rbd_warn(rbd_dev, "failed to break object map lock: %d", ret);
		return ret;
	}

	broke_lock = true;
	goto again;
}