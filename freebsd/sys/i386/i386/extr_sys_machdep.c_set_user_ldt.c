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
struct mdproc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_user_ldt_locked (struct mdproc*) ; 

void
set_user_ldt(struct mdproc *mdp)
{

	mtx_lock_spin(&dt_lock);
	set_user_ldt_locked(mdp);
	mtx_unlock_spin(&dt_lock);
}