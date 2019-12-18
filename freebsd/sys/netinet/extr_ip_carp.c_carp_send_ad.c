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
struct carp_softc {TYPE_1__* sc_carpdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK_ASSERT (struct carp_softc*) ; 
 int /*<<< orphan*/  CARP_UNLOCK (struct carp_softc*) ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carp_send_ad_locked (struct carp_softc*) ; 

__attribute__((used)) static void
carp_send_ad(void *v)
{
	struct carp_softc *sc = v;

	CARP_LOCK_ASSERT(sc);
	CURVNET_SET(sc->sc_carpdev->if_vnet);
	carp_send_ad_locked(sc);
	CURVNET_RESTORE();
	CARP_UNLOCK(sc);
}