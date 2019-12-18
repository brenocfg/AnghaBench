#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnxt_softc {TYPE_1__* scctx; int /*<<< orphan*/  media; } ;
typedef  TYPE_2__* if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_5__ {scalar_t__ if_mtu; } ;
struct TYPE_4__ {scalar_t__ isc_max_frame_size; } ;

/* Variables and functions */
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  bnxt_add_media_types (struct bnxt_softc*) ; 
 int /*<<< orphan*/  bnxt_create_config_sysctls_post (struct bnxt_softc*) ; 
 int /*<<< orphan*/  bnxt_create_ver_sysctls (struct bnxt_softc*) ; 
 int bnxt_probe_phy (struct bnxt_softc*) ; 
 TYPE_2__* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bnxt_attach_post(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	if_t ifp = iflib_get_ifp(ctx);
	int rc;

	bnxt_create_config_sysctls_post(softc);

	/* Update link state etc... */
	rc = bnxt_probe_phy(softc);
	if (rc)
		goto failed;

	/* Needs to be done after probing the phy */
	bnxt_create_ver_sysctls(softc);
	bnxt_add_media_types(softc);
	ifmedia_set(softc->media, IFM_ETHER | IFM_AUTO);

	softc->scctx->isc_max_frame_size = ifp->if_mtu + ETHER_HDR_LEN +
	    ETHER_CRC_LEN;

failed:
	return rc;
}