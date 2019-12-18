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
struct TYPE_2__ {int /*<<< orphan*/ * is_pic; } ;
struct xenisrc {int xi_vector; int xi_type; TYPE_1__ xi_intsrc; } ;
typedef  enum evtchn_type { ____Placeholder_evtchn_type } evtchn_type ;

/* Variables and functions */
 int EVTCHN_TYPE_PIRQ ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  M_XENINTR ; 
 int M_ZERO ; 
 int NR_EVENT_CHANNELS ; 
 int first_evtchn_irq ; 
 int /*<<< orphan*/ * intr_lookup_source (int) ; 
 int /*<<< orphan*/  intr_register_source (TYPE_1__*) ; 
 struct xenisrc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int xen_intr_auto_vector_count ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 
 int /*<<< orphan*/  xen_intr_pic ; 
 int /*<<< orphan*/  xen_intr_pirq_pic ; 

__attribute__((used)) static struct xenisrc *
xen_intr_alloc_isrc(enum evtchn_type type, int vector)
{
	static int warned;
	struct xenisrc *isrc;

	KASSERT(mtx_owned(&xen_intr_isrc_lock), ("Evtchn alloc lock not held"));

	if (xen_intr_auto_vector_count > NR_EVENT_CHANNELS) {
		if (!warned) {
			warned = 1;
			printf("xen_intr_alloc: Event channels exhausted.\n");
		}
		return (NULL);
	}

	if (type != EVTCHN_TYPE_PIRQ) {
		vector = first_evtchn_irq + xen_intr_auto_vector_count;
		xen_intr_auto_vector_count++;
	}

	KASSERT((intr_lookup_source(vector) == NULL),
	    ("Trying to use an already allocated vector"));

	mtx_unlock(&xen_intr_isrc_lock);
	isrc = malloc(sizeof(*isrc), M_XENINTR, M_WAITOK | M_ZERO);
	isrc->xi_intsrc.is_pic =
	    (type == EVTCHN_TYPE_PIRQ) ? &xen_intr_pirq_pic : &xen_intr_pic;
	isrc->xi_vector = vector;
	isrc->xi_type = type;
	intr_register_source(&isrc->xi_intsrc);
	mtx_lock(&xen_intr_isrc_lock);

	return (isrc);
}