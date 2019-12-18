#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct resource {int dummy; } ;
struct TYPE_4__ {TYPE_1__** pcpu; } ;
struct gic_v3_softc {TYPE_2__ gic_redists; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
struct TYPE_3__ {struct resource res; } ;

/* Variables and functions */
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_read_8 (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 

uint64_t
gic_r_read_8(device_t dev, bus_size_t offset)
{
	struct gic_v3_softc *sc;
	struct resource *rdist;

	sc = device_get_softc(dev);
	rdist = &sc->gic_redists.pcpu[PCPU_GET(cpuid)]->res;
	return (bus_read_8(rdist, offset));
}