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
struct ioat_softc {int version; } ;
typedef  int /*<<< orphan*/  bus_dmaengine_t ;

/* Variables and functions */
 struct ioat_softc* to_ioat_softc (int /*<<< orphan*/ ) ; 

int
ioat_get_hwversion(bus_dmaengine_t dmaengine)
{
	struct ioat_softc *ioat;

	ioat = to_ioat_softc(dmaengine);
	return (ioat->version);
}