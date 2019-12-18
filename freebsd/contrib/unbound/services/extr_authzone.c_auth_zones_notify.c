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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct module_env {int dummy; } ;
struct auth_zones {int /*<<< orphan*/  lock; } ;
struct auth_xfer {int /*<<< orphan*/  lock; } ;
struct auth_master {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 struct auth_xfer* auth_xfer_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  az_xfr_allowed_notify (struct auth_xfer*,struct sockaddr_storage*,int /*<<< orphan*/ ,struct auth_master**) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfr_process_notify (struct auth_xfer*,struct module_env*,int,int /*<<< orphan*/ ,struct auth_master*) ; 

int auth_zones_notify(struct auth_zones* az, struct module_env* env,
	uint8_t* nm, size_t nmlen, uint16_t dclass,
	struct sockaddr_storage* addr, socklen_t addrlen, int has_serial,
	uint32_t serial, int* refused)
{
	struct auth_xfer* xfr;
	struct auth_master* fromhost = NULL;
	/* see which zone this is */
	lock_rw_rdlock(&az->lock);
	xfr = auth_xfer_find(az, nm, nmlen, dclass);
	if(!xfr) {
		lock_rw_unlock(&az->lock);
		/* no such zone, refuse the notify */
		*refused = 1;
		return 0;
	}
	lock_basic_lock(&xfr->lock);
	lock_rw_unlock(&az->lock);
	
	/* check access list for notifies */
	if(!az_xfr_allowed_notify(xfr, addr, addrlen, &fromhost)) {
		lock_basic_unlock(&xfr->lock);
		/* notify not allowed, refuse the notify */
		*refused = 1;
		return 0;
	}

	/* process the notify */
	xfr_process_notify(xfr, env, has_serial, serial, fromhost);
	return 1;
}