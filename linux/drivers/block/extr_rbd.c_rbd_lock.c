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
struct rbd_device {char* lock_cookie; int /*<<< orphan*/  header_oloc; int /*<<< orphan*/  header_oid; TYPE_2__* rbd_client; } ;
struct ceph_osd_client {int dummy; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CLS_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  RBD_LOCK_NAME ; 
 int /*<<< orphan*/  RBD_LOCK_TAG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __rbd_is_lock_owner (struct rbd_device*) ; 
 int /*<<< orphan*/  __rbd_lock (struct rbd_device*,char*) ; 
 int ceph_cls_lock (struct ceph_osd_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_lock_cookie (struct rbd_device*,char*) ; 

__attribute__((used)) static int rbd_lock(struct rbd_device *rbd_dev)
{
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	char cookie[32];
	int ret;

	WARN_ON(__rbd_is_lock_owner(rbd_dev) ||
		rbd_dev->lock_cookie[0] != '\0');

	format_lock_cookie(rbd_dev, cookie);
	ret = ceph_cls_lock(osdc, &rbd_dev->header_oid, &rbd_dev->header_oloc,
			    RBD_LOCK_NAME, CEPH_CLS_LOCK_EXCLUSIVE, cookie,
			    RBD_LOCK_TAG, "", 0);
	if (ret)
		return ret;

	__rbd_lock(rbd_dev, cookie);
	return 0;
}