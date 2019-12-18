#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union descriptor {int dummy; } descriptor ;
struct proc_ldt {int ldt_len; int ldt_refcnt; scalar_t__ ldt_base; int /*<<< orphan*/  ldt_sd; scalar_t__ ldt_active; } ;
struct mdproc {struct proc_ldt* md_ldt; } ;
struct TYPE_3__ {unsigned int ssd_base; int ssd_limit; } ;

/* Variables and functions */
 size_t GUSERLDT_SEL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_SUBPROC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NEW_MAX_LD (int) ; 
 int NLDT ; 
 int /*<<< orphan*/  bcopy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  dt_lock ; 
 TYPE_1__* gdt_segs ; 
 scalar_t__ ldt ; 
 struct proc_ldt* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ pmap_trm_alloc (int,int) ; 
 int /*<<< orphan*/  ssdtosd (TYPE_1__*,int /*<<< orphan*/ *) ; 

struct proc_ldt *
user_ldt_alloc(struct mdproc *mdp, int len)
{
	struct proc_ldt *pldt, *new_ldt;

	mtx_assert(&dt_lock, MA_OWNED);
	mtx_unlock_spin(&dt_lock);
	new_ldt = malloc(sizeof(struct proc_ldt), M_SUBPROC, M_WAITOK);

	new_ldt->ldt_len = len = NEW_MAX_LD(len);
	new_ldt->ldt_base = pmap_trm_alloc(len * sizeof(union descriptor),
	    M_WAITOK | M_ZERO);
	new_ldt->ldt_refcnt = 1;
	new_ldt->ldt_active = 0;

	mtx_lock_spin(&dt_lock);
	gdt_segs[GUSERLDT_SEL].ssd_base = (unsigned)new_ldt->ldt_base;
	gdt_segs[GUSERLDT_SEL].ssd_limit = len * sizeof(union descriptor) - 1;
	ssdtosd(&gdt_segs[GUSERLDT_SEL], &new_ldt->ldt_sd);

	if ((pldt = mdp->md_ldt) != NULL) {
		if (len > pldt->ldt_len)
			len = pldt->ldt_len;
		bcopy(pldt->ldt_base, new_ldt->ldt_base,
		    len * sizeof(union descriptor));
	} else
		bcopy(ldt, new_ldt->ldt_base, sizeof(union descriptor) * NLDT);
	
	return (new_ldt);
}