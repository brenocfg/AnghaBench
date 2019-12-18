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
struct cbb_softc {scalar_t__ cbdev; TYPE_1__* exca; } ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {scalar_t__ pccarddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 struct cbb_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int /*<<< orphan*/ ) ; 

void
cbb_child_detached(device_t brdev, device_t child)
{
	struct cbb_softc *sc = device_get_softc(brdev);

	/* I'm not sure we even need this */
	if (child != sc->cbdev && child != sc->exca[0].pccarddev)
		device_printf(brdev, "Unknown child detached: %s\n",
		    device_get_nameunit(child));
}