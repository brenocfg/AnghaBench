#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {int /*<<< orphan*/ * irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ alloc_resource (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gusc_intr ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,void**) ; 

__attribute__((used)) static int
gusc_attach(device_t dev)
{
	sc_p scp;
	void *ih;

	scp = device_get_softc(dev);

	bzero(scp, sizeof(*scp));

	scp->dev = dev;
	if (alloc_resource(scp)) {
		release_resource(scp);
		return (ENXIO);
	}

	if (scp->irq != NULL)
		snd_setup_intr(dev, scp->irq, 0, gusc_intr, scp, &ih);
	bus_generic_attach(dev);

	return (0);
}