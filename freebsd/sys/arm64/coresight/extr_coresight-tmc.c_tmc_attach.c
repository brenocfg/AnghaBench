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
struct tmc_softc {int /*<<< orphan*/  pdata; int /*<<< orphan*/  res; void* dev; } ;
struct coresight_desc {int /*<<< orphan*/  dev_type; void* dev; int /*<<< orphan*/  pdata; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORESIGHT_TMC ; 
 int ENXIO ; 
 scalar_t__ bus_alloc_resources (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coresight_get_platform_data (void*) ; 
 int /*<<< orphan*/  coresight_register (struct coresight_desc*) ; 
 struct tmc_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  tmc_spec ; 

__attribute__((used)) static int
tmc_attach(device_t dev)
{
	struct coresight_desc desc;
	struct tmc_softc *sc;

	sc = device_get_softc(dev);

	sc->dev = dev;

	if (bus_alloc_resources(dev, tmc_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	sc->pdata = coresight_get_platform_data(dev);
	desc.pdata = sc->pdata;
	desc.dev = dev;
	desc.dev_type = CORESIGHT_TMC;
	coresight_register(&desc);

	return (0);
}