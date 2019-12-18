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
struct rbd_client {TYPE_2__* client; } ;
struct ceph_options {int dummy; } ;
struct TYPE_4__ {TYPE_1__* options; } ;
struct TYPE_3__ {int /*<<< orphan*/  mount_timeout; } ;

/* Variables and functions */
 struct rbd_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  ceph_destroy_options (struct ceph_options*) ; 
 int ceph_wait_for_latest_osdmap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rbd_client* rbd_client_create (struct ceph_options*) ; 
 struct rbd_client* rbd_client_find (struct ceph_options*) ; 
 int /*<<< orphan*/  rbd_put_client (struct rbd_client*) ; 
 int /*<<< orphan*/  rbd_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static struct rbd_client *rbd_get_client(struct ceph_options *ceph_opts)
{
	struct rbd_client *rbdc;
	int ret;

	mutex_lock(&client_mutex);
	rbdc = rbd_client_find(ceph_opts);
	if (rbdc) {
		ceph_destroy_options(ceph_opts);

		/*
		 * Using an existing client.  Make sure ->pg_pools is up to
		 * date before we look up the pool id in do_rbd_add().
		 */
		ret = ceph_wait_for_latest_osdmap(rbdc->client,
					rbdc->client->options->mount_timeout);
		if (ret) {
			rbd_warn(NULL, "failed to get latest osdmap: %d", ret);
			rbd_put_client(rbdc);
			rbdc = ERR_PTR(ret);
		}
	} else {
		rbdc = rbd_client_create(ceph_opts);
	}
	mutex_unlock(&client_mutex);

	return rbdc;
}