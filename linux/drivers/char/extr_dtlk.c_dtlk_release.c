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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
#define  DTLK_MINOR 128 
 int /*<<< orphan*/  TRACE_RET ; 
 int /*<<< orphan*/  TRACE_TEXT (char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtlk_timer ; 
 int iminor (struct inode*) ; 

__attribute__((used)) static int dtlk_release(struct inode *inode, struct file *file)
{
	TRACE_TEXT("(dtlk_release");

	switch (iminor(inode)) {
	case DTLK_MINOR:
		break;

	default:
		break;
	}
	TRACE_RET;
	
	del_timer_sync(&dtlk_timer);

	return 0;
}