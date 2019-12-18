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
typedef  union descriptor {int dummy; } descriptor ;
struct proc_ldt {scalar_t__ ldt_refcnt; int ldt_len; int /*<<< orphan*/  ldt_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_SUBPROC ; 
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  free (struct proc_ldt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_trm_free (int /*<<< orphan*/ ,int) ; 

void
user_ldt_deref(struct proc_ldt *pldt)
{

	mtx_assert(&dt_lock, MA_OWNED);
	if (--pldt->ldt_refcnt == 0) {
		mtx_unlock_spin(&dt_lock);
		pmap_trm_free(pldt->ldt_base, pldt->ldt_len *
		    sizeof(union descriptor));
		free(pldt, M_SUBPROC);
	} else
		mtx_unlock_spin(&dt_lock);
}