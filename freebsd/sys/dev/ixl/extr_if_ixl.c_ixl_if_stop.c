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
struct ixl_vsi {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  qtag; scalar_t__ iw_enabled; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_disable_rings (struct ixl_pf*,struct ixl_vsi*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_disable_rings_intr (struct ixl_vsi*) ; 
 scalar_t__ ixl_enable_iwarp ; 
 int /*<<< orphan*/  ixl_iw_pf_stop (struct ixl_pf*) ; 

void
ixl_if_stop(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;

	INIT_DEBUGOUT("ixl_if_stop: begin\n");

	// TODO: This may need to be reworked
#ifdef IXL_IW
	/* Stop iWARP device */
	if (ixl_enable_iwarp && pf->iw_enabled)
		ixl_iw_pf_stop(pf);
#endif

	ixl_disable_rings_intr(vsi);
	ixl_disable_rings(pf, vsi, &pf->qtag);
}