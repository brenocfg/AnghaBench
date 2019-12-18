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
struct filemon {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  filemon_close_log (struct filemon*) ; 
 int /*<<< orphan*/  filemon_drop (struct filemon*) ; 
 int /*<<< orphan*/  filemon_untrack_processes (struct filemon*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
filemon_dtr(void *data)
{
	struct filemon *filemon = data;

	if (filemon == NULL)
		return;

	sx_xlock(&filemon->lock);
	/*
	 * Detach the filemon.  It cannot be inherited after this.
	 */
	filemon_untrack_processes(filemon);
	filemon_close_log(filemon);
	filemon_drop(filemon);
}