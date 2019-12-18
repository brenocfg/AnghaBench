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
struct xenisrc {int /*<<< orphan*/ * xi_cookie; int /*<<< orphan*/  xi_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intr_remove_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 struct xenisrc* xen_intr_isrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 
 int /*<<< orphan*/  xen_intr_release_isrc (struct xenisrc*) ; 

void
xen_intr_unbind(xen_intr_handle_t *port_handlep)
{
	struct xenisrc *isrc;

	KASSERT(port_handlep != NULL,
	    ("NULL xen_intr_handle_t passed to xen_intr_unbind"));

	isrc = xen_intr_isrc(*port_handlep);
	*port_handlep = NULL;
	if (isrc == NULL)
		return;

	mtx_lock(&xen_intr_isrc_lock);
	if (refcount_release(&isrc->xi_refcount) == 0) {
		mtx_unlock(&xen_intr_isrc_lock);
		return;
	}
	mtx_unlock(&xen_intr_isrc_lock);

	if (isrc->xi_cookie != NULL)
		intr_remove_handler(isrc->xi_cookie);
	xen_intr_release_isrc(isrc);
}