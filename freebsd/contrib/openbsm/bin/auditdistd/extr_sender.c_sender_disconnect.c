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
struct TYPE_2__ {int adh_reset; char* adh_trail_name; int /*<<< orphan*/  adh_remoteaddr; scalar_t__ adh_trail_offset; int /*<<< orphan*/ * adh_remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_CONCAT2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* adhost ; 
 int /*<<< orphan*/  adist_free_list ; 
 int /*<<< orphan*/  adist_recv_list ; 
 int /*<<< orphan*/  adist_remote_lock ; 
 int /*<<< orphan*/  adist_remote_mtx ; 
 int /*<<< orphan*/  adist_send_list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sender_disconnect(void)
{

	rw_wlock(&adist_remote_lock);
	/*
	 * Check for a race between dropping rlock and acquiring wlock -
	 * another thread can close connection in-between.
	 */
	if (adhost->adh_remote == NULL) {
		rw_unlock(&adist_remote_lock);
		return;
	}
	pjdlog_debug(2, "Closing connection to %s.", adhost->adh_remoteaddr);
	proto_close(adhost->adh_remote);
	mtx_lock(&adist_remote_mtx);
	adhost->adh_remote = NULL;
	adhost->adh_reset = true;
	adhost->adh_trail_name[0] = '\0';
	adhost->adh_trail_offset = 0;
	mtx_unlock(&adist_remote_mtx);
	rw_unlock(&adist_remote_lock);

	pjdlog_warning("Disconnected from %s.", adhost->adh_remoteaddr);

	/* Move all in-flight requests back onto free list. */
	QUEUE_CONCAT2(&adist_free_list, &adist_send_list, &adist_recv_list);
}