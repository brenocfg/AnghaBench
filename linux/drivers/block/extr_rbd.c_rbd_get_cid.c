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
struct rbd_device {int /*<<< orphan*/  watch_mutex; int /*<<< orphan*/  watch_cookie; TYPE_1__* rbd_client; } ;
struct rbd_client_id {int /*<<< orphan*/  handle; int /*<<< orphan*/  gid; } ;
struct TYPE_2__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_client_gid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rbd_client_id rbd_get_cid(struct rbd_device *rbd_dev)
{
	struct rbd_client_id cid;

	mutex_lock(&rbd_dev->watch_mutex);
	cid.gid = ceph_client_gid(rbd_dev->rbd_client->client);
	cid.handle = rbd_dev->watch_cookie;
	mutex_unlock(&rbd_dev->watch_mutex);
	return cid;
}