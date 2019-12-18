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
typedef  int /*<<< orphan*/  uint32_t ;
struct cbb_softc {scalar_t__ cardok; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CBB_CARD_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBB_SOCKET_STATE ; 
 int /*<<< orphan*/  cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

int
cbb_child_present(device_t parent, device_t child)
{
	struct cbb_softc *sc = (struct cbb_softc *)device_get_softc(parent);
	uint32_t sockstate;

	sockstate = cbb_get(sc, CBB_SOCKET_STATE);
	return (CBB_CARD_PRESENT(sockstate) && sc->cardok);
}