#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  csa_res ;
struct TYPE_4__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int ENXIO ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 scalar_t__ csa_downloadimage (int /*<<< orphan*/ *) ; 
 scalar_t__ csa_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  csa_resetdsp (int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csa_resume(device_t dev)
{
	csa_res *resp;
	sc_p scp;

	scp = device_get_softc(dev);
	resp = &scp->res;

	/* Initialize the chip. */
	if (csa_initialize(scp))
		return (ENXIO);

	/* Reset the Processor. */
	csa_resetdsp(resp);

	/* Download the Processor Image to the processor. */
	if (csa_downloadimage(resp))
		return (ENXIO);

	return (bus_generic_resume(dev));
}