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
struct chipc_softc {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPC_CHIPST ; 
 int /*<<< orphan*/  bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
chipc_read_chipst(device_t dev)
{
	struct chipc_softc *sc = device_get_softc(dev);
	return (bhnd_bus_read_4(sc->core, CHIPC_CHIPST));
}