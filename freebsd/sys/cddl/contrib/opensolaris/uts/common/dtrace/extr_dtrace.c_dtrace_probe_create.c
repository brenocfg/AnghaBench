#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_7__ {int dtpr_id; int dtpr_aframes; int /*<<< orphan*/ * dtpr_provider; void* dtpr_arg; void* dtpr_name; void* dtpr_func; void* dtpr_mod; scalar_t__ dtpr_gen; } ;
typedef  TYPE_1__ dtrace_probe_t ;
typedef  int dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int VM_BESTFIT ; 
 int VM_SLEEP ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (TYPE_1__**,TYPE_1__**,size_t) ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/  dtrace_byfunc ; 
 int /*<<< orphan*/  dtrace_bymod ; 
 int /*<<< orphan*/  dtrace_byname ; 
 int /*<<< orphan*/  dtrace_hash_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_membar_producer () ; 
 int dtrace_nprobes ; 
 int /*<<< orphan*/  dtrace_probegen ; 
 TYPE_1__** dtrace_probes ; 
 int /*<<< orphan*/ * dtrace_provider ; 
 void* dtrace_strdup (char const*) ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,size_t) ; 
 void* kmem_zalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,int,int) ; 

dtrace_id_t
dtrace_probe_create(dtrace_provider_id_t prov, const char *mod,
    const char *func, const char *name, int aframes, void *arg)
{
	dtrace_probe_t *probe, **probes;
	dtrace_provider_t *provider = (dtrace_provider_t *)prov;
	dtrace_id_t id;

	if (provider == dtrace_provider) {
		ASSERT(MUTEX_HELD(&dtrace_lock));
	} else {
		mutex_enter(&dtrace_lock);
	}

#ifdef illumos
	id = (dtrace_id_t)(uintptr_t)vmem_alloc(dtrace_arena, 1,
	    VM_BESTFIT | VM_SLEEP);
#else
	id = alloc_unr(dtrace_arena);
#endif
	probe = kmem_zalloc(sizeof (dtrace_probe_t), KM_SLEEP);

	probe->dtpr_id = id;
	probe->dtpr_gen = dtrace_probegen++;
	probe->dtpr_mod = dtrace_strdup(mod);
	probe->dtpr_func = dtrace_strdup(func);
	probe->dtpr_name = dtrace_strdup(name);
	probe->dtpr_arg = arg;
	probe->dtpr_aframes = aframes;
	probe->dtpr_provider = provider;

	dtrace_hash_add(dtrace_bymod, probe);
	dtrace_hash_add(dtrace_byfunc, probe);
	dtrace_hash_add(dtrace_byname, probe);

	if (id - 1 >= dtrace_nprobes) {
		size_t osize = dtrace_nprobes * sizeof (dtrace_probe_t *);
		size_t nsize = osize << 1;

		if (nsize == 0) {
			ASSERT(osize == 0);
			ASSERT(dtrace_probes == NULL);
			nsize = sizeof (dtrace_probe_t *);
		}

		probes = kmem_zalloc(nsize, KM_SLEEP);

		if (dtrace_probes == NULL) {
			ASSERT(osize == 0);
			dtrace_probes = probes;
			dtrace_nprobes = 1;
		} else {
			dtrace_probe_t **oprobes = dtrace_probes;

			bcopy(oprobes, probes, osize);
			dtrace_membar_producer();
			dtrace_probes = probes;

			dtrace_sync();

			/*
			 * All CPUs are now seeing the new probes array; we can
			 * safely free the old array.
			 */
			kmem_free(oprobes, osize);
			dtrace_nprobes <<= 1;
		}

		ASSERT(id - 1 < dtrace_nprobes);
	}

	ASSERT(dtrace_probes[id - 1] == NULL);
	dtrace_probes[id - 1] = probe;

	if (provider != dtrace_provider)
		mutex_exit(&dtrace_lock);

	return (id);
}