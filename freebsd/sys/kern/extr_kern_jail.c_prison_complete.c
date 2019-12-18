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
struct prison {scalar_t__ pr_uref; int /*<<< orphan*/  pr_mtx; } ;

/* Variables and functions */
 int PD_DEREF ; 
 int PD_DEUREF ; 
 int PD_LIST_XLOCKED ; 
 int PD_LOCKED ; 
 int /*<<< orphan*/  allprison_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prison_deref (struct prison*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prison_complete(void *context, int pending)
{
	struct prison *pr = context;

	sx_xlock(&allprison_lock);
	mtx_lock(&pr->pr_mtx);
	prison_deref(pr, pr->pr_uref
	    ? PD_DEREF | PD_DEUREF | PD_LOCKED | PD_LIST_XLOCKED
	    : PD_LOCKED | PD_LIST_XLOCKED);
}