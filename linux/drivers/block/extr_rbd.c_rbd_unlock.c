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
struct rbd_device {char* lock_cookie; int /*<<< orphan*/  released_lock_work; int /*<<< orphan*/  task_wq; int /*<<< orphan*/  lock_state; int /*<<< orphan*/  header_oloc; int /*<<< orphan*/  header_oid; TYPE_2__* rbd_client; } ;
struct ceph_osd_client {int dummy; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  RBD_LOCK_NAME ; 
 int /*<<< orphan*/  RBD_LOCK_STATE_UNLOCKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __rbd_is_lock_owner (struct rbd_device*) ; 
 int ceph_cls_unlock (struct ceph_osd_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_empty_cid ; 
 int /*<<< orphan*/  rbd_set_owner_cid (struct rbd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,int) ; 

__attribute__((used)) static void rbd_unlock(struct rbd_device *rbd_dev)
{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	int ret;

	WARN_ON(!__rbd_is_lock_owner(rbd_dev) ||
		rbd_dev->lock_cookie[0] == '\0');

	ret = ceph_cls_unlock(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			      RBD_LOCK_NAME, rbd_dev->lock_cookie);
	if (ret && ret != -ENOENT)
		rbd_warn(rbd_dev, "failed to unlock header: %d", ret);

	/* treat errors as the image is unlocked */
	rbd_dev->lock_state = RBD_LOCK_STATE_UNLOCKED;
	rbd_dev->lock_cookie[0] = '\0';
	rbd_set_owner_cid(rbd_dev, &rbd_empty_cid);
	queue_work(rbd_dev->task_wq, &rbd_dev->released_lock_work);
}