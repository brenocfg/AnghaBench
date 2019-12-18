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
struct config_auth {int /*<<< orphan*/  fallback_enabled; int /*<<< orphan*/  for_upstream; scalar_t__ for_downstream; int /*<<< orphan*/  zonefile; scalar_t__ urls; scalar_t__ masters; int /*<<< orphan*/  name; } ;
struct auth_zones {int have_downstream; int /*<<< orphan*/  lock; } ;
struct auth_zone {int zone_is_slave; int /*<<< orphan*/  lock; int /*<<< orphan*/  fallback_enabled; int /*<<< orphan*/  for_upstream; scalar_t__ for_downstream; scalar_t__ zone_deleted; } ;
struct auth_xfer {int /*<<< orphan*/  lock; TYPE_2__* task_transfer; TYPE_1__* task_probe; } ;
struct TYPE_4__ {int /*<<< orphan*/  masters; } ;
struct TYPE_3__ {int /*<<< orphan*/  masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_zone_set_zonefile (struct auth_zone*,int /*<<< orphan*/ ) ; 
 struct auth_xfer* auth_zones_find_or_add_xfer (struct auth_zones*,struct auth_zone*) ; 
 struct auth_zone* auth_zones_find_or_add_zone (struct auth_zones*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfer_set_masters (int /*<<< orphan*/ *,struct config_auth*,int) ; 

__attribute__((used)) static int
auth_zones_cfg(struct auth_zones* az, struct config_auth* c)
{
	struct auth_zone* z;
	struct auth_xfer* x = NULL;

	/* create zone */
	lock_rw_wrlock(&az->lock);
	if(!(z=auth_zones_find_or_add_zone(az, c->name))) {
		lock_rw_unlock(&az->lock);
		return 0;
	}
	if(c->masters || c->urls) {
		if(!(x=auth_zones_find_or_add_xfer(az, z))) {
			lock_rw_unlock(&az->lock);
			lock_rw_unlock(&z->lock);
			return 0;
		}
	}
	if(c->for_downstream)
		az->have_downstream = 1;
	lock_rw_unlock(&az->lock);

	/* set options */
	z->zone_deleted = 0;
	if(!auth_zone_set_zonefile(z, c->zonefile)) {
		if(x) {
			lock_basic_unlock(&x->lock);
		}
		lock_rw_unlock(&z->lock);
		return 0;
	}
	z->for_downstream = c->for_downstream;
	z->for_upstream = c->for_upstream;
	z->fallback_enabled = c->fallback_enabled;

	/* xfer zone */
	if(x) {
		z->zone_is_slave = 1;
		/* set options on xfer zone */
		if(!xfer_set_masters(&x->task_probe->masters, c, 0)) {
			lock_basic_unlock(&x->lock);
			lock_rw_unlock(&z->lock);
			return 0;
		}
		if(!xfer_set_masters(&x->task_transfer->masters, c, 1)) {
			lock_basic_unlock(&x->lock);
			lock_rw_unlock(&z->lock);
			return 0;
		}
		lock_basic_unlock(&x->lock);
	}

	lock_rw_unlock(&z->lock);
	return 1;
}