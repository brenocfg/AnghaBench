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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int cmx_alloc_resources (int /*<<< orphan*/ ) ; 
 int cmx_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmx_init_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmx_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cmx_pccard_attach(device_t dev)
{
	int rv = 0;
	cmx_init_softc(dev);

	if ((rv = cmx_alloc_resources(dev)) != 0) {
		device_printf(dev, "cmx_alloc_resources() failed!\n");
		cmx_release_resources(dev);
		return rv;
	}

	if ((rv = cmx_attach(dev)) != 0) {
		device_printf(dev, "cmx_attach() failed!\n");
		cmx_release_resources(dev);
		return rv;
	}

	device_printf(dev, "attached\n");
	return 0;
}