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
struct cbb_softc {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CBB_16BIT_CARD ; 
 int cbb_cardbus_power_enable_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cbb_pcic_power_enable_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
cbb_power_enable_socket(device_t brdev, device_t child)
{
	struct cbb_softc *sc = device_get_softc(brdev);

	if (sc->flags & CBB_16BIT_CARD)
		return (cbb_pcic_power_enable_socket(brdev, child));
	return (cbb_cardbus_power_enable_socket(brdev, child));
}