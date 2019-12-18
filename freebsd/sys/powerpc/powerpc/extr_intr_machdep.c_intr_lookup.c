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
typedef  scalar_t__ u_int ;
struct powerpc_intr {scalar_t__ irq; int vector; size_t cntindex; int /*<<< orphan*/ * cntp; int /*<<< orphan*/  pi_cpuset; scalar_t__ ipi; scalar_t__ fwcode; int /*<<< orphan*/ * pic; int /*<<< orphan*/  pol; int /*<<< orphan*/  trig; int /*<<< orphan*/ * priv; int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTR_POLARITY_CONFORM ; 
 int /*<<< orphan*/  INTR_TRIGGER_CONFORM ; 
 int /*<<< orphan*/  M_INTR ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  all_cpus ; 
 size_t atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct powerpc_intr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_table_lock ; 
 int /*<<< orphan*/ * intrcnt ; 
 int /*<<< orphan*/  intrcnt_index ; 
 int /*<<< orphan*/  intrcnt_setname (char*,size_t) ; 
 struct powerpc_intr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int num_io_irqs ; 
 int nvectors ; 
 struct powerpc_intr** powerpc_intrs ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static struct powerpc_intr *
intr_lookup(u_int irq)
{
	char intrname[16];
	struct powerpc_intr *i, *iscan;
	int vector;

	mtx_lock(&intr_table_lock);
	for (vector = 0; vector < nvectors; vector++) {
		i = powerpc_intrs[vector];
		if (i != NULL && i->irq == irq) {
			mtx_unlock(&intr_table_lock);
			return (i);
		}
	}

	i = malloc(sizeof(*i), M_INTR, M_NOWAIT);
	if (i == NULL) {
		mtx_unlock(&intr_table_lock);
		return (NULL);
	}

	i->event = NULL;
	i->cntp = NULL;
	i->priv = NULL;
	i->trig = INTR_TRIGGER_CONFORM;
	i->pol = INTR_POLARITY_CONFORM;
	i->irq = irq;
	i->pic = NULL;
	i->vector = -1;
	i->fwcode = 0;
	i->ipi = 0;

#ifdef SMP
	i->pi_cpuset = all_cpus;
#else
	CPU_SETOF(0, &i->pi_cpuset);
#endif

	for (vector = 0; vector < num_io_irqs && vector <= nvectors;
	    vector++) {
		iscan = powerpc_intrs[vector];
		if (iscan != NULL && iscan->irq == irq)
			break;
		if (iscan == NULL && i->vector == -1)
			i->vector = vector;
		iscan = NULL;
	}

	if (iscan == NULL && i->vector != -1) {
		powerpc_intrs[i->vector] = i;
		i->cntindex = atomic_fetchadd_int(&intrcnt_index, 1);
		i->cntp = &intrcnt[i->cntindex];
		sprintf(intrname, "irq%u:", i->irq);
		intrcnt_setname(intrname, i->cntindex);
		nvectors++;
	}
	mtx_unlock(&intr_table_lock);

	if (iscan != NULL || i->vector == -1) {
		free(i, M_INTR);
		i = iscan;
	}

	return (i);
}