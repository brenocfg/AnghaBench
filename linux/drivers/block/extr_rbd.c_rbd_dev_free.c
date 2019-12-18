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
struct rbd_device {scalar_t__ watch_state; scalar_t__ lock_state; struct rbd_device* opts; int /*<<< orphan*/  spec; int /*<<< orphan*/  rbd_client; struct rbd_device* config_info; int /*<<< orphan*/  header_oloc; int /*<<< orphan*/  header_oid; } ;

/* Variables and functions */
 scalar_t__ RBD_LOCK_STATE_UNLOCKED ; 
 scalar_t__ RBD_WATCH_STATE_UNREGISTERED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_oid_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_oloc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_put_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_spec_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbd_dev_free(struct rbd_device *rbd_dev)
{
	WARN_ON(rbd_dev->watch_state != RBD_WATCH_STATE_UNREGISTERED);
	WARN_ON(rbd_dev->lock_state != RBD_LOCK_STATE_UNLOCKED);

	ceph_oid_destroy(&rbd_dev->header_oid);
	ceph_oloc_destroy(&rbd_dev->header_oloc);
	kfree(rbd_dev->config_info);

	rbd_put_client(rbd_dev->rbd_client);
	rbd_spec_put(rbd_dev->spec);
	kfree(rbd_dev->opts);
	kfree(rbd_dev);
}