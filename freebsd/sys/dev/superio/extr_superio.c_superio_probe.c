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
struct siosc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 struct siosc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int superio_detect (int /*<<< orphan*/ ,int,struct siosc*) ; 

__attribute__((used)) static int
superio_probe(device_t dev)
{
	struct siosc *sc;
	int error;

	/* Make sure we do not claim some ISA PNP device. */
	if (isa_get_logicalid(dev) != 0)
		return (ENXIO);

	/*
	 * XXX We can populate the softc now only because we return
	 * BUS_PROBE_SPECIFIC
	 */
	sc = device_get_softc(dev);
	error = superio_detect(dev, true, sc);
	if (error != 0)
		return (error);
	return (BUS_PROBE_SPECIFIC);
}