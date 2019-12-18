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
struct funnel_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORESIGHT_LAR ; 
 int /*<<< orphan*/  CORESIGHT_UNLOCK ; 
 int /*<<< orphan*/  FUNNEL_DEVICEID ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct funnel_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
funnel_init(device_t dev)
{
	struct funnel_softc *sc;

	sc = device_get_softc(dev);

	/* Unlock Coresight */
	bus_write_4(sc->res, CORESIGHT_LAR, CORESIGHT_UNLOCK);

	dprintf("Device ID: %x\n", bus_read_4(sc->res, FUNNEL_DEVICEID));

	return (0);
}