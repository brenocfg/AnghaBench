#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int natids; TYPE_1__* atid_tab; scalar_t__ atids_in_use; TYPE_1__* afree; int /*<<< orphan*/  atid_lock; } ;
struct adapter {struct tid_info tids; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
t4_init_atid_table(struct adapter *sc)
{
	struct tid_info *t;
	int i;

	t = &sc->tids;
	if (t->natids == 0)
		return;

	MPASS(t->atid_tab == NULL);

	t->atid_tab = malloc(t->natids * sizeof(*t->atid_tab), M_CXGBE,
	    M_ZERO | M_WAITOK);
	mtx_init(&t->atid_lock, "atid lock", NULL, MTX_DEF);
	t->afree = t->atid_tab;
	t->atids_in_use = 0;
	for (i = 1; i < t->natids; i++)
		t->atid_tab[i - 1].next = &t->atid_tab[i];
	t->atid_tab[t->natids - 1].next = NULL;
}