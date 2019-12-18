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
struct bnxt_softc {int wol; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTSUP ; 
 int IFCAP_WOL_MAGIC ; 
 scalar_t__ bnxt_hwrm_alloc_wol_fltr (struct bnxt_softc*) ; 
 scalar_t__ bnxt_hwrm_free_wol_fltr (struct bnxt_softc*) ; 
 int /*<<< orphan*/  bnxt_wol_supported (struct bnxt_softc*) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_wol_config(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	if_t ifp = iflib_get_ifp(ctx);

	if (!softc)
		return -EBUSY;

	if (!bnxt_wol_supported(softc))
		return -ENOTSUP;

	if (if_getcapabilities(ifp) & IFCAP_WOL_MAGIC) {
		if (!softc->wol) {
			if (bnxt_hwrm_alloc_wol_fltr(softc))
				return -EBUSY;
			softc->wol = 1;
		}
	} else {
		if (softc->wol) {
			if (bnxt_hwrm_free_wol_fltr(softc))
				return -EBUSY;
			softc->wol = 0;
		}
	}

	return 0;
}