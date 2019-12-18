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
 int /*<<< orphan*/  LIST_REMOVE (struct file_lock*,int /*<<< orphan*/ ) ; 
 int NFS_GRANTED ; 
 int /*<<< orphan*/  nfslocklist ; 

enum nfslock_status
delete_nfslock(struct file_lock *fl)
{

	LIST_REMOVE(fl, nfslocklist);

	return (NFS_GRANTED);
}