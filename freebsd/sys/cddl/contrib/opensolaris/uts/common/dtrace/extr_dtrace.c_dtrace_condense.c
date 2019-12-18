#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void (* dtps_enable ) (void*,dtrace_id_t,void*) ;int /*<<< orphan*/  (* dtps_destroy ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  dtpv_arg; TYPE_1__ dtpv_pops; } ;
typedef  TYPE_2__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_10__ {struct TYPE_10__* dtpr_name; struct TYPE_10__* dtpr_func; struct TYPE_10__* dtpr_mod; int /*<<< orphan*/  dtpr_arg; int /*<<< orphan*/ * dtpr_ecb; TYPE_2__* dtpr_provider; } ;
typedef  TYPE_3__ dtrace_probe_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/  dtrace_byfunc ; 
 int /*<<< orphan*/  dtrace_bymod ; 
 int /*<<< orphan*/  dtrace_byname ; 
 int /*<<< orphan*/  dtrace_hash_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_nprobes ; 
 scalar_t__ dtrace_nullop ; 
 TYPE_3__** dtrace_probes ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int strlen (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,void*,int) ; 

int
dtrace_condense(dtrace_provider_id_t id)
{
	dtrace_provider_t *prov = (dtrace_provider_t *)id;
	int i;
	dtrace_probe_t *probe;

	/*
	 * Make sure this isn't the dtrace provider itself.
	 */
	ASSERT(prov->dtpv_pops.dtps_enable !=
	    (void (*)(void *, dtrace_id_t, void *))dtrace_nullop);

	mutex_enter(&dtrace_provider_lock);
	mutex_enter(&dtrace_lock);

	/*
	 * Attempt to destroy the probes associated with this provider.
	 */
	for (i = 0; i < dtrace_nprobes; i++) {
		if ((probe = dtrace_probes[i]) == NULL)
			continue;

		if (probe->dtpr_provider != prov)
			continue;

		if (probe->dtpr_ecb != NULL)
			continue;

		dtrace_probes[i] = NULL;

		dtrace_hash_remove(dtrace_bymod, probe);
		dtrace_hash_remove(dtrace_byfunc, probe);
		dtrace_hash_remove(dtrace_byname, probe);

		prov->dtpv_pops.dtps_destroy(prov->dtpv_arg, i + 1,
		    probe->dtpr_arg);
		kmem_free(probe->dtpr_mod, strlen(probe->dtpr_mod) + 1);
		kmem_free(probe->dtpr_func, strlen(probe->dtpr_func) + 1);
		kmem_free(probe->dtpr_name, strlen(probe->dtpr_name) + 1);
		kmem_free(probe, sizeof (dtrace_probe_t));
#ifdef illumos
		vmem_free(dtrace_arena, (void *)((uintptr_t)i + 1), 1);
#else
		free_unr(dtrace_arena, i + 1);
#endif
	}

	mutex_exit(&dtrace_lock);
	mutex_exit(&dtrace_provider_lock);

	return (0);
}