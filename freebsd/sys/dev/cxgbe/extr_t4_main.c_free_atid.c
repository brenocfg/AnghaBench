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
union aopen_entry {union aopen_entry* next; } ;
struct tid_info {int /*<<< orphan*/  atid_lock; int /*<<< orphan*/  atids_in_use; union aopen_entry* afree; union aopen_entry* atid_tab; } ;
struct adapter {struct tid_info tids; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
free_atid(struct adapter *sc, int atid)
{
	struct tid_info *t = &sc->tids;
	union aopen_entry *p = &t->atid_tab[atid];

	mtx_lock(&t->atid_lock);
	p->next = t->afree;
	t->afree = p;
	t->atids_in_use--;
	mtx_unlock(&t->atid_lock);
}