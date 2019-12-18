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
typedef  int /*<<< orphan*/ * xen_intr_handle_t ;
struct xenisrc {size_t xi_port; int /*<<< orphan*/  xi_intsrc; int /*<<< orphan*/  xi_vector; int /*<<< orphan*/  xi_refcount; } ;
typedef  size_t evtchn_port_t ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  enum evtchn_type { ____Placeholder_evtchn_type } evtchn_type ;
typedef  int /*<<< orphan*/ * driver_intr_t ;
typedef  int /*<<< orphan*/ * driver_filter_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int EVTCHN_TYPE_PORT ; 
 int /*<<< orphan*/  XEN_ALLOCATE_VECTOR ; 
 int /*<<< orphan*/  intr_next_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int xen_intr_add_handler (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 
 struct xenisrc* xen_intr_alloc_isrc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_assign_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xenisrc* xen_intr_find_unused_isrc (int) ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 
 struct xenisrc** xen_intr_port_to_isrc ; 
 int /*<<< orphan*/  xen_intr_release_isrc (struct xenisrc*) ; 

__attribute__((used)) static int
xen_intr_bind_isrc(struct xenisrc **isrcp, evtchn_port_t local_port,
    enum evtchn_type type, const char *intr_owner, driver_filter_t filter,
    driver_intr_t handler, void *arg, enum intr_type flags,
    xen_intr_handle_t *port_handlep)
{
	struct xenisrc *isrc;
	int error;

	*isrcp = NULL;
	if (port_handlep == NULL) {
		printf("%s: xen_intr_bind_isrc: Bad event handle\n",
		    intr_owner);
		return (EINVAL);
	}

	mtx_lock(&xen_intr_isrc_lock);
	isrc = xen_intr_find_unused_isrc(type);
	if (isrc == NULL) {
		isrc = xen_intr_alloc_isrc(type, XEN_ALLOCATE_VECTOR);
		if (isrc == NULL) {
			mtx_unlock(&xen_intr_isrc_lock);
			return (ENOSPC);
		}
	}
	isrc->xi_port = local_port;
	xen_intr_port_to_isrc[local_port] = isrc;
	refcount_init(&isrc->xi_refcount, 1);
	mtx_unlock(&xen_intr_isrc_lock);

	/* Assign the opaque handler (the event channel port) */
	*port_handlep = &isrc->xi_vector;

#ifdef SMP
	if (type == EVTCHN_TYPE_PORT) {
		/*
		 * By default all interrupts are assigned to vCPU#0
		 * unless specified otherwise, so shuffle them to balance
		 * the interrupt load.
		 */
		xen_intr_assign_cpu(&isrc->xi_intsrc, intr_next_cpu(0));
	}
#endif

	if (filter == NULL && handler == NULL) {
		/*
		 * No filter/handler provided, leave the event channel
		 * masked and without a valid handler, the caller is
		 * in charge of setting that up.
		 */
		*isrcp = isrc;
		return (0);
	}

	error = xen_intr_add_handler(intr_owner, filter, handler, arg, flags,
	    *port_handlep);
	if (error != 0) {
		xen_intr_release_isrc(isrc);
		return (error);
	}
	*isrcp = isrc;
	return (0);
}