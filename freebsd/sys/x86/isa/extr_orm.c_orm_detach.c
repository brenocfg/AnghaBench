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
struct orm_softc {int rnum; int /*<<< orphan*/ * res; int /*<<< orphan*/ * rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
orm_detach(device_t dev)
{
	int			i;
	struct orm_softc	*sc = device_get_softc(dev);
	
	for (i = 0; i < sc->rnum; i++)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->rid[i],
		    sc->res[i]);
	return (0);
}