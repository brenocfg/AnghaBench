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
typedef  scalar_t__ u32 ;
struct rbd_device {int /*<<< orphan*/  header_oloc; int /*<<< orphan*/  header_oid; TYPE_1__* rbd_client; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  cookie; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct ceph_locker {TYPE_3__ id; TYPE_2__ info; } ;
struct ceph_client {int /*<<< orphan*/  osdc; int /*<<< orphan*/  monc; } ;
struct TYPE_4__ {struct ceph_client* client; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENTITY_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBD_LOCK_NAME ; 
 int ceph_cls_break_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_free_lockers (struct ceph_locker*,scalar_t__) ; 
 int ceph_monc_blacklist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int find_watcher (struct rbd_device*,struct ceph_locker*) ; 
 int get_lock_owner_info (struct rbd_device*,struct ceph_locker**,scalar_t__*) ; 
 int rbd_lock (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int rbd_try_lock(struct rbd_device *rbd_dev)
{
	struct ceph_client *client = rbd_dev->rbd_client->client;
	struct ceph_locker *lockers;
	u32 num_lockers;
	int ret;

	for (;;) {
		ret = rbd_lock(rbd_dev);
		if (ret != -EBUSY)
			return ret;

		/* determine if the current lock holder is still alive */
		ret = get_lock_owner_info(rbd_dev, &lockers, &num_lockers);
		if (ret)
			return ret;

		if (num_lockers == 0)
			goto again;

		ret = find_watcher(rbd_dev, lockers);
		if (ret)
			goto out; /* request lock or error */

		rbd_warn(rbd_dev, "breaking header lock owned by %s%llu",
			 ENTITY_NAME(lockers[0].id.name));

		ret = ceph_monc_blacklist_add(&client->monc,
					      &lockers[0].info.addr);
		if (ret) {
			rbd_warn(rbd_dev, "blacklist of %s%llu failed: %d",
				 ENTITY_NAME(lockers[0].id.name), ret);
			goto out;
		}

		ret = ceph_cls_break_lock(&client->osdc, &rbd_dev->header_oid,
					  &rbd_dev->header_oloc, RBD_LOCK_NAME,
					  lockers[0].id.cookie,
					  &lockers[0].id.name);
		if (ret && ret != -ENOENT)
			goto out;

again:
		ceph_free_lockers(lockers, num_lockers);
	}

out:
	ceph_free_lockers(lockers, num_lockers);
	return ret;
}