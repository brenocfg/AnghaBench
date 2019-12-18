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
struct tcl_addr {scalar_t__ count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 

void
tcl_close_connection(struct tcl_addr* tcl)
{
	if(tcl) {
		lock_quick_lock(&tcl->lock);
		log_assert(tcl->count > 0);
		tcl->count--;
		lock_quick_unlock(&tcl->lock);
	}
}