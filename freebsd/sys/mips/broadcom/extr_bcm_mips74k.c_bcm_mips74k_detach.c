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
struct bcm_mips74k_softc {int /*<<< orphan*/  mem; int /*<<< orphan*/  mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bcm_mips_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_mips74k_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_mips74k_detach(device_t dev)
{
	struct bcm_mips74k_softc	*sc;
	int				 error;

	sc = device_get_softc(dev);

	if ((error = bcm_mips_detach(dev)))
		return (error);

	bus_release_resource(dev, SYS_RES_MEMORY, sc->mem_rid, sc->mem);

	return (0);
}