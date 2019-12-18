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
struct TYPE_2__ {scalar_t__ adh_role; int /*<<< orphan*/  adh_remoteaddr; int /*<<< orphan*/ * adh_remote; } ;

/* Variables and functions */
 scalar_t__ ADIST_ROLE_SENDER ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 TYPE_1__* adhost ; 
 int /*<<< orphan*/  adist_remote_lock ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sender_connect () ; 

__attribute__((used)) static void
guard_check_connection(void)
{

	PJDLOG_ASSERT(adhost->adh_role == ADIST_ROLE_SENDER);

	rw_rlock(&adist_remote_lock);
	if (adhost->adh_remote != NULL) {
		rw_unlock(&adist_remote_lock);
		pjdlog_debug(3, "remote_guard: Connection to %s is ok.",
		    adhost->adh_remoteaddr);
		return;
	}

	/*
	 * Upgrade the lock. It doesn't have to be atomic as no other thread
	 * can change connection status from disconnected to connected.
	 */
	rw_unlock(&adist_remote_lock);
	pjdlog_debug(1, "remote_guard: Reconnecting to %s.",
	    adhost->adh_remoteaddr);
	if (sender_connect() == 0) {
		pjdlog_info("Successfully reconnected to %s.",
		    adhost->adh_remoteaddr);
	} else {
		pjdlog_debug(1, "remote_guard: Reconnect to %s failed.",
		    adhost->adh_remoteaddr);
	}
}