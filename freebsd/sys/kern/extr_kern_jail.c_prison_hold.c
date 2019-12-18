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
struct prison {int /*<<< orphan*/  pr_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prison_hold_locked (struct prison*) ; 

void
prison_hold(struct prison *pr)
{

	mtx_lock(&pr->pr_mtx);
	prison_hold_locked(pr);
	mtx_unlock(&pr->pr_mtx);
}