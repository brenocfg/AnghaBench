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
typedef  int /*<<< orphan*/  uint16_t ;
struct module_env {int dummy; } ;
struct auth_zones {int /*<<< orphan*/  lock; } ;
struct auth_xfer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct auth_xfer* auth_xfer_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfr_process_notify (struct auth_xfer*,struct module_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int auth_zones_startprobesequence(struct auth_zones* az,
	struct module_env* env, uint8_t* nm, size_t nmlen, uint16_t dclass)
{
	struct auth_xfer* xfr;
	lock_rw_rdlock(&az->lock);
	xfr = auth_xfer_find(az, nm, nmlen, dclass);
	if(!xfr) {
		lock_rw_unlock(&az->lock);
		return 0;
	}
	lock_basic_lock(&xfr->lock);
	lock_rw_unlock(&az->lock);

	xfr_process_notify(xfr, env, 0, 0, NULL);
	return 1;
}