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
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_PROC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SX_DUPOK ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  UMA_ZONE_NOFREE ; 
 int /*<<< orphan*/  allproc ; 
 int /*<<< orphan*/  allproc_lock ; 
 void* hashinit (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int maxproc ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pgrphash ; 
 void* pgrphashtbl ; 
 int pidhash ; 
 int pidhashlock ; 
 void* pidhashtbl ; 
 int /*<<< orphan*/ * pidhashtbl_lock ; 
 int /*<<< orphan*/  ppeers_lock ; 
 int /*<<< orphan*/  proc_ctor ; 
 int /*<<< orphan*/  proc_dtor ; 
 int /*<<< orphan*/  proc_fini ; 
 int /*<<< orphan*/  proc_init ; 
 int /*<<< orphan*/  proc_zone ; 
 int /*<<< orphan*/  procid_lock ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sched_sizeof_proc () ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_init_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uihashinit () ; 
 int /*<<< orphan*/  uma_zcreate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
procinit(void)
{
	u_long i;

	sx_init(&allproc_lock, "allproc");
	sx_init(&proctree_lock, "proctree");
	mtx_init(&ppeers_lock, "p_peers", NULL, MTX_DEF);
	mtx_init(&procid_lock, "procid", NULL, MTX_DEF);
	LIST_INIT(&allproc);
	pidhashtbl = hashinit(maxproc / 4, M_PROC, &pidhash);
	pidhashlock = (pidhash + 1) / 64;
	if (pidhashlock > 0)
		pidhashlock--;
	pidhashtbl_lock = malloc(sizeof(*pidhashtbl_lock) * (pidhashlock + 1),
	    M_PROC, M_WAITOK | M_ZERO);
	for (i = 0; i < pidhashlock + 1; i++)
		sx_init_flags(&pidhashtbl_lock[i], "pidhash", SX_DUPOK);
	pgrphashtbl = hashinit(maxproc / 4, M_PROC, &pgrphash);
	proc_zone = uma_zcreate("PROC", sched_sizeof_proc(),
	    proc_ctor, proc_dtor, proc_init, proc_fini,
	    UMA_ALIGN_PTR, UMA_ZONE_NOFREE);
	uihashinit();
}