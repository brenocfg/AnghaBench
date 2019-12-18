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
struct xenisrc {int xi_pirq; int xi_activehi; int xi_edgetrigger; } ;
struct physdev_map_pirq {int index; int pirq; int /*<<< orphan*/  type; int /*<<< orphan*/  domid; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int EINVAL ; 
 int /*<<< orphan*/  EVTCHN_TYPE_PIRQ ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_map_pirq*) ; 
 int INTR_POLARITY_HIGH ; 
 int INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAP_PIRQ_TYPE_GSI ; 
 int /*<<< orphan*/  PHYSDEVOP_map_pirq ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 struct xenisrc* xen_intr_alloc_isrc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 

int
xen_register_pirq(int vector, enum intr_trigger trig, enum intr_polarity pol)
{
	struct physdev_map_pirq map_pirq;
	struct xenisrc *isrc;
	int error;

	if (vector == 0)
		return (EINVAL);

	if (bootverbose)
		printf("xen: register IRQ#%d\n", vector);

	map_pirq.domid = DOMID_SELF;
	map_pirq.type = MAP_PIRQ_TYPE_GSI;
	map_pirq.index = vector;
	map_pirq.pirq = vector;

	error = HYPERVISOR_physdev_op(PHYSDEVOP_map_pirq, &map_pirq);
	if (error) {
		printf("xen: unable to map IRQ#%d\n", vector);
		return (error);
	}

	mtx_lock(&xen_intr_isrc_lock);
	isrc = xen_intr_alloc_isrc(EVTCHN_TYPE_PIRQ, vector);
	mtx_unlock(&xen_intr_isrc_lock);
	KASSERT((isrc != NULL), ("xen: unable to allocate isrc for interrupt"));
	isrc->xi_pirq = vector;
	isrc->xi_activehi = pol == INTR_POLARITY_HIGH ? 1 : 0;
	isrc->xi_edgetrigger = trig == INTR_TRIGGER_EDGE ? 1 : 0;

	return (0);
}