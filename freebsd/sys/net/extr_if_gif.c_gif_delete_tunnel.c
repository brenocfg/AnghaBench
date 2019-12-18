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
struct gif_softc {scalar_t__ gif_family; int /*<<< orphan*/  gif_hdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct gif_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* GIF2IFP (struct gif_softc*) ; 
 int /*<<< orphan*/  GIF_WAIT () ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  M_GIF ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gif_ioctl_sx ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srchash ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gif_delete_tunnel(struct gif_softc *sc)
{

	sx_assert(&gif_ioctl_sx, SA_XLOCKED);
	if (sc->gif_family != 0) {
		CK_LIST_REMOVE(sc, srchash);
		CK_LIST_REMOVE(sc, chain);
		/* Wait until it become safe to free gif_hdr */
		GIF_WAIT();
		free(sc->gif_hdr, M_GIF);
	}
	sc->gif_family = 0;
	GIF2IFP(sc)->if_drv_flags &= ~IFF_DRV_RUNNING;
	if_link_state_change(GIF2IFP(sc), LINK_STATE_DOWN);
}