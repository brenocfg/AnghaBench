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
struct module_env {TYPE_1__* auth_zones; } ;
struct auth_zone {int zone_expired; int /*<<< orphan*/  lock; } ;
struct auth_xfer {int zone_expired; int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct auth_zone* auth_zone_find (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
auth_xfer_set_expired(struct auth_xfer* xfr, struct module_env* env,
	int expired)
{
	struct auth_zone* z;

	/* expire xfr */
	lock_basic_lock(&xfr->lock);
	xfr->zone_expired = expired;
	lock_basic_unlock(&xfr->lock);

	/* find auth_zone */
	lock_rw_rdlock(&env->auth_zones->lock);
	z = auth_zone_find(env->auth_zones, xfr->name, xfr->namelen,
		xfr->dclass);
	if(!z) {
		lock_rw_unlock(&env->auth_zones->lock);
		return;
	}
	lock_rw_wrlock(&z->lock);
	lock_rw_unlock(&env->auth_zones->lock);

	/* expire auth_zone */
	z->zone_expired = expired;
	lock_rw_unlock(&z->lock);
}