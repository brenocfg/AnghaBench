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
typedef  int /*<<< orphan*/  uint32_t ;
struct module_env {int dummy; } ;
struct auth_xfer {int /*<<< orphan*/  lock; } ;
struct auth_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfr_note_notify_serial (struct auth_xfer*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfr_serial_means_update (struct auth_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfr_start_probe (struct auth_xfer*,struct module_env*,struct auth_master*) ; 

__attribute__((used)) static void
xfr_process_notify(struct auth_xfer* xfr, struct module_env* env,
	int has_serial, uint32_t serial, struct auth_master* fromhost)
{
	/* if the serial of notify is older than we have, don't fetch
	 * a zone, we already have it */
	if(has_serial && !xfr_serial_means_update(xfr, serial)) {
		lock_basic_unlock(&xfr->lock);
		return;
	}
	/* start new probe with this addr src, or note serial */
	if(!xfr_start_probe(xfr, env, fromhost)) {
		/* not started because already in progress, note the serial */
		xfr_note_notify_serial(xfr, has_serial, serial);
		lock_basic_unlock(&xfr->lock);
	}
	/* successful end of start_probe unlocked xfr->lock */
}