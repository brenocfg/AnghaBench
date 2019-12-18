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
struct firewire_softc {TYPE_1__* fc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWBUSNOTREADY ; 
 int /*<<< orphan*/  bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct firewire_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
firewire_resume(device_t dev)
{
	struct firewire_softc *sc;

	sc = device_get_softc(dev);
	sc->fc->status = FWBUSNOTREADY;

	bus_generic_resume(dev);

	return (0);
}