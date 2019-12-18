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
struct xformsw {int xf_cntr; } ;

/* Variables and functions */
 int IPSEC_MODULE_ENABLED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct xformsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFORMS_LOCK () ; 
 int /*<<< orphan*/  XFORMS_UNLOCK () ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  ipsec_kmod_drain (int*) ; 
 int /*<<< orphan*/  key_delete_xform (struct xformsw*) ; 

void
xform_detach(void *data)
{
	struct xformsw *xsp = (struct xformsw *)data;

	XFORMS_LOCK();
	LIST_REMOVE(xsp, chain);
	XFORMS_UNLOCK();

	/* Delete all SAs related to this xform. */
	key_delete_xform(xsp);
	if (xsp->xf_cntr & IPSEC_MODULE_ENABLED)
		ipsec_kmod_drain(&xsp->xf_cntr);
}