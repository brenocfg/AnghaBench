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

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct file_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debuglog (char*) ; 
 int /*<<< orphan*/  nfslocklist ; 

void
remove_blockingfilelock(struct file_lock *fl)
{

	debuglog("Entering remove_blockingfilelock\n");

	LIST_REMOVE(fl, nfslocklist);

	debuglog("Exiting remove_blockingfilelock\n");
}