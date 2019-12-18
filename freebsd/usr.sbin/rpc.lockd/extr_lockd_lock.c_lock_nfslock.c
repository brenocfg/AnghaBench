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
struct file_lock {int dummy; } ;
typedef  enum nfslock_status { ____Placeholder_nfslock_status } nfslock_status ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct file_lock*,int /*<<< orphan*/ ) ; 
 int NFS_GRANTED ; 
 int NFS_GRANTED_DUPLICATE ; 
 int /*<<< orphan*/  debuglog (char*) ; 
 int /*<<< orphan*/  dump_filelock (struct file_lock*) ; 
 int /*<<< orphan*/  nfslocklist ; 
 int /*<<< orphan*/  nfslocklist_head ; 
 int test_nfslock (struct file_lock*,struct file_lock**) ; 

enum nfslock_status
lock_nfslock(struct file_lock *fl)
{
	enum nfslock_status retval;
	struct file_lock *dummy_fl;

	dummy_fl = NULL;

	debuglog("Entering lock_nfslock...\n");

	retval = test_nfslock(fl,&dummy_fl);

	if (retval == NFS_GRANTED || retval == NFS_GRANTED_DUPLICATE) {
		debuglog("Inserting lock...\n");
		dump_filelock(fl);
		LIST_INSERT_HEAD(&nfslocklist_head, fl, nfslocklist);
	}

	debuglog("Exiting lock_nfslock...\n");

	return (retval);
}