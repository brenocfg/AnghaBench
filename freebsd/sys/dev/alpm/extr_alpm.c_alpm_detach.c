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
struct alpm_softc {scalar_t__ res; int /*<<< orphan*/  lock; int /*<<< orphan*/ * smbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMBBA ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct alpm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
alpm_detach(device_t dev)
{
	struct alpm_softc *alpm = device_get_softc(dev);

	if (alpm->smbus) {
		device_delete_child(dev, alpm->smbus);
		alpm->smbus = NULL;
	}
	mtx_destroy(&alpm->lock);

	if (alpm->res)
		bus_release_resource(dev, SYS_RES_IOPORT, SMBBA, alpm->res);

	return (0);
}