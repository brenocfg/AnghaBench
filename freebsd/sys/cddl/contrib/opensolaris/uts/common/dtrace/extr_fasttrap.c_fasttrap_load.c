#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong_t ;
typedef  int /*<<< orphan*/  fasttrap_bucket_t ;
struct TYPE_12__ {int fth_nent; int fth_mask; TYPE_2__* fth_table; } ;
struct TYPE_11__ {int fth_nent; int fth_mask; TYPE_3__* fth_table; } ;
struct TYPE_10__ {int fth_nent; int fth_mask; TYPE_1__* fth_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  ftb_mtx; } ;
struct TYPE_8__ {int /*<<< orphan*/  ftb_mtx; } ;
struct TYPE_7__ {int /*<<< orphan*/  ftb_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DDI_DEV_T_ANY ; 
 int /*<<< orphan*/  DDI_PROP_DONTPASS ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FASTTRAP_MAX_DEFAULT ; 
 int FASTTRAP_PROCS_DEFAULT_SIZE ; 
 int FASTTRAP_PROVIDERS_DEFAULT_SIZE ; 
 int FASTTRAP_TPOINTS_DEFAULT_SIZE ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 scalar_t__ ISP2 (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  UID_ROOT ; 
 void* ddi_getprop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devi ; 
 int /*<<< orphan*/ * dtrace_fasttrap_exec ; 
 int /*<<< orphan*/ * dtrace_fasttrap_exit ; 
 int /*<<< orphan*/ * dtrace_fasttrap_fork ; 
 int /*<<< orphan*/  dtrace_meta_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fasttrap_cdev ; 
 int /*<<< orphan*/  fasttrap_cdevsw ; 
 int /*<<< orphan*/  fasttrap_cleanup_mtx ; 
 int /*<<< orphan*/  fasttrap_cleanup_proc ; 
 int /*<<< orphan*/  fasttrap_count_mtx ; 
 int /*<<< orphan*/  fasttrap_exec_exit ; 
 int /*<<< orphan*/  fasttrap_fork ; 
 int fasttrap_highbit (int) ; 
 void* fasttrap_max ; 
 int /*<<< orphan*/  fasttrap_meta_id ; 
 int /*<<< orphan*/  fasttrap_mops ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup_cb ; 
 TYPE_6__ fasttrap_procs ; 
 TYPE_5__ fasttrap_provs ; 
 int /*<<< orphan*/  fasttrap_thread_dtor ; 
 int /*<<< orphan*/  fasttrap_thread_dtor_tag ; 
 scalar_t__ fasttrap_total ; 
 int /*<<< orphan*/  fasttrap_tp_lock ; 
 TYPE_4__ fasttrap_tpoints ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int kproc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thread_dtor ; 
 int tpoints_hash_size ; 

__attribute__((used)) static int
fasttrap_load(void)
{
	ulong_t nent;
	int i, ret;

        /* Create the /dev/dtrace/fasttrap entry. */
        fasttrap_cdev = make_dev(&fasttrap_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600,
            "dtrace/fasttrap");

	mtx_init(&fasttrap_cleanup_mtx, "fasttrap clean", "dtrace", MTX_DEF);
	mutex_init(&fasttrap_count_mtx, "fasttrap count mtx", MUTEX_DEFAULT,
	    NULL);

#ifdef illumos
	fasttrap_max = ddi_getprop(DDI_DEV_T_ANY, devi, DDI_PROP_DONTPASS,
	    "fasttrap-max-probes", FASTTRAP_MAX_DEFAULT);
#endif
	fasttrap_total = 0;

	/*
	 * Conjure up the tracepoints hashtable...
	 */
#ifdef illumos
	nent = ddi_getprop(DDI_DEV_T_ANY, devi, DDI_PROP_DONTPASS,
	    "fasttrap-hash-size", FASTTRAP_TPOINTS_DEFAULT_SIZE);
#else
	nent = tpoints_hash_size;
#endif

	if (nent == 0 || nent > 0x1000000)
		nent = FASTTRAP_TPOINTS_DEFAULT_SIZE;

	tpoints_hash_size = nent;

	if (ISP2(nent))
		fasttrap_tpoints.fth_nent = nent;
	else
		fasttrap_tpoints.fth_nent = 1 << fasttrap_highbit(nent);
	ASSERT(fasttrap_tpoints.fth_nent > 0);
	fasttrap_tpoints.fth_mask = fasttrap_tpoints.fth_nent - 1;
	fasttrap_tpoints.fth_table = kmem_zalloc(fasttrap_tpoints.fth_nent *
	    sizeof (fasttrap_bucket_t), KM_SLEEP);
#ifndef illumos
	for (i = 0; i < fasttrap_tpoints.fth_nent; i++)
		mutex_init(&fasttrap_tpoints.fth_table[i].ftb_mtx,
		    "tracepoints bucket mtx", MUTEX_DEFAULT, NULL);
#endif

	/*
	 * ... and the providers hash table...
	 */
	nent = FASTTRAP_PROVIDERS_DEFAULT_SIZE;
	if (ISP2(nent))
		fasttrap_provs.fth_nent = nent;
	else
		fasttrap_provs.fth_nent = 1 << fasttrap_highbit(nent);
	ASSERT(fasttrap_provs.fth_nent > 0);
	fasttrap_provs.fth_mask = fasttrap_provs.fth_nent - 1;
	fasttrap_provs.fth_table = kmem_zalloc(fasttrap_provs.fth_nent *
	    sizeof (fasttrap_bucket_t), KM_SLEEP);
#ifndef illumos
	for (i = 0; i < fasttrap_provs.fth_nent; i++)
		mutex_init(&fasttrap_provs.fth_table[i].ftb_mtx, 
		    "providers bucket mtx", MUTEX_DEFAULT, NULL);
#endif

	ret = kproc_create(fasttrap_pid_cleanup_cb, NULL,
	    &fasttrap_cleanup_proc, 0, 0, "ftcleanup");
	if (ret != 0) {
		destroy_dev(fasttrap_cdev);
#ifndef illumos
		for (i = 0; i < fasttrap_provs.fth_nent; i++)
			mutex_destroy(&fasttrap_provs.fth_table[i].ftb_mtx);
		for (i = 0; i < fasttrap_tpoints.fth_nent; i++)
			mutex_destroy(&fasttrap_tpoints.fth_table[i].ftb_mtx);
#endif
		kmem_free(fasttrap_provs.fth_table, fasttrap_provs.fth_nent *
		    sizeof (fasttrap_bucket_t));
		mtx_destroy(&fasttrap_cleanup_mtx);
		mutex_destroy(&fasttrap_count_mtx);
		return (ret);
	}


	/*
	 * ... and the procs hash table.
	 */
	nent = FASTTRAP_PROCS_DEFAULT_SIZE;
	if (ISP2(nent))
		fasttrap_procs.fth_nent = nent;
	else
		fasttrap_procs.fth_nent = 1 << fasttrap_highbit(nent);
	ASSERT(fasttrap_procs.fth_nent > 0);
	fasttrap_procs.fth_mask = fasttrap_procs.fth_nent - 1;
	fasttrap_procs.fth_table = kmem_zalloc(fasttrap_procs.fth_nent *
	    sizeof (fasttrap_bucket_t), KM_SLEEP);
#ifndef illumos
	for (i = 0; i < fasttrap_procs.fth_nent; i++)
		mutex_init(&fasttrap_procs.fth_table[i].ftb_mtx,
		    "processes bucket mtx", MUTEX_DEFAULT, NULL);

	rm_init(&fasttrap_tp_lock, "fasttrap tracepoint");

	/*
	 * This event handler must run before kdtrace_thread_dtor() since it
	 * accesses the thread's struct kdtrace_thread.
	 */
	fasttrap_thread_dtor_tag = EVENTHANDLER_REGISTER(thread_dtor,
	    fasttrap_thread_dtor, NULL, EVENTHANDLER_PRI_FIRST);
#endif

	/*
	 * Install our hooks into fork(2), exec(2), and exit(2).
	 */
	dtrace_fasttrap_fork = &fasttrap_fork;
	dtrace_fasttrap_exit = &fasttrap_exec_exit;
	dtrace_fasttrap_exec = &fasttrap_exec_exit;

	(void) dtrace_meta_register("fasttrap", &fasttrap_mops, NULL,
	    &fasttrap_meta_id);

	return (0);
}