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
typedef  scalar_t__ uint32_t ;
struct hn_softc {int hn_link_flags; int /*<<< orphan*/  hn_ifp; } ;

/* Variables and functions */
 int HN_LINK_FLAG_LINKUP ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ NDIS_MEDIA_STATE_CONNECTED ; 
 int hn_rndis_get_linkstatus (struct hn_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_link_status(struct hn_softc *sc)
{
	uint32_t link_status;
	int error;

	error = hn_rndis_get_linkstatus(sc, &link_status);
	if (error) {
		/* XXX what to do? */
		return;
	}

	if (link_status == NDIS_MEDIA_STATE_CONNECTED)
		sc->hn_link_flags |= HN_LINK_FLAG_LINKUP;
	else
		sc->hn_link_flags &= ~HN_LINK_FLAG_LINKUP;
	if_link_state_change(sc->hn_ifp,
	    (sc->hn_link_flags & HN_LINK_FLAG_LINKUP) ?
	    LINK_STATE_UP : LINK_STATE_DOWN);
}