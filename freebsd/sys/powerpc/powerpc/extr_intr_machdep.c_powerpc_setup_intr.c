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
typedef  int /*<<< orphan*/  u_int ;
struct powerpc_intr {int pi_domain; scalar_t__ trig; scalar_t__ pic; scalar_t__ pol; int /*<<< orphan*/  priv; int /*<<< orphan*/  vector; int /*<<< orphan*/  intline; int /*<<< orphan*/  pi_cpuset; int /*<<< orphan*/  fwcode; int /*<<< orphan*/  cntindex; TYPE_1__* event; } ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
struct TYPE_3__ {int /*<<< orphan*/  ie_fullname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 scalar_t__ INTR_POLARITY_CONFORM ; 
 scalar_t__ INTR_TRIGGER_CONFORM ; 
 scalar_t__ INTR_TRIGGER_INVALID ; 
 int /*<<< orphan*/  PIC_BIND (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIC_CONFIG (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PIC_ENABLE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIC_TRANSLATE_CODE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/ * cpuset_domain ; 
 int intr_event_add_handler (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,void**) ; 
 int intr_event_create (TYPE_1__**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct powerpc_intr* intr_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_priority (int) ; 
 int /*<<< orphan*/  intr_table_lock ; 
 int /*<<< orphan*/  intrcnt_setname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powerpc_assign_intr_cpu ; 
 int /*<<< orphan*/  powerpc_intr_eoi ; 
 int /*<<< orphan*/  powerpc_intr_post_ithread ; 
 int /*<<< orphan*/  powerpc_intr_pre_ithread ; 
 int powerpc_map_irq (struct powerpc_intr*) ; 
 scalar_t__ root_pic ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
powerpc_setup_intr(const char *name, u_int irq, driver_filter_t filter,
    driver_intr_t handler, void *arg, enum intr_type flags, void **cookiep,
    int domain)
{
	struct powerpc_intr *i;
	int error, enable = 0;

	i = intr_lookup(irq);
	if (i == NULL)
		return (ENOMEM);

	if (i->event == NULL) {
		error = intr_event_create(&i->event, (void *)i, 0, irq,
		    powerpc_intr_pre_ithread, powerpc_intr_post_ithread,
		    powerpc_intr_eoi, powerpc_assign_intr_cpu, "irq%u:", irq);
		if (error)
			return (error);

		enable = 1;
	}

	error = intr_event_add_handler(i->event, name, filter, handler, arg,
	    intr_priority(flags), flags, cookiep);
	if (error)
		return (error);
	i->pi_domain = domain;
	if (strcmp(name, "IPI") != 0)  {
		CPU_ZERO(&i->pi_cpuset);
		CPU_COPY(&cpuset_domain[domain], &i->pi_cpuset);
	}
	mtx_lock(&intr_table_lock);
	intrcnt_setname(i->event->ie_fullname, i->cntindex);
	mtx_unlock(&intr_table_lock);

	if (!cold) {
		error = powerpc_map_irq(i);

		if (!error) {
			if (i->trig == INTR_TRIGGER_INVALID)
				PIC_TRANSLATE_CODE(i->pic, i->intline,
				    i->fwcode, &i->trig, &i->pol);
	
			if (i->trig != INTR_TRIGGER_CONFORM ||
			    i->pol != INTR_POLARITY_CONFORM)
				PIC_CONFIG(i->pic, i->intline, i->trig, i->pol);

			if (i->pic == root_pic)
				PIC_BIND(i->pic, i->intline, i->pi_cpuset, &i->priv);

			if (enable)
				PIC_ENABLE(i->pic, i->intline, i->vector,
				    &i->priv);
		}
	}
	return (error);
}