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
struct file_lock {scalar_t__ blocking; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct file_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockedlocklist_head ; 
 int /*<<< orphan*/  debuglog (char*) ; 
 scalar_t__ duplicate_block (struct file_lock*) ; 
 int /*<<< orphan*/  nfslocklist ; 

void
add_blockingfilelock(struct file_lock *fl)
{
	debuglog("Entering add_blockingfilelock\n");

	/*
	 * A blocking lock request _should_ never be duplicated as a client
	 * that is already blocked shouldn't be able to request another
	 * lock. Alas, there are some buggy clients that do request the same
	 * lock repeatedly. Make sure only unique locks are on the blocked
	 * lock list.
	 */
	if (duplicate_block(fl)) {
		debuglog("Exiting add_blockingfilelock: already blocked\n");
		return;
	}

	/*
	 * Clear the blocking flag so that it can be reused without
	 * adding it to the blocking queue a second time
	 */

	fl->blocking = 0;
	LIST_INSERT_HEAD(&blockedlocklist_head, fl, nfslocklist);

	debuglog("Exiting add_blockingfilelock: added blocked lock\n");
}