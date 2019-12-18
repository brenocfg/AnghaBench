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
struct csa_midi_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * io; int /*<<< orphan*/  io_rid; int /*<<< orphan*/  mpu; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct csa_midi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mpu401_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
midicsa_detach(device_t dev)
{
	struct csa_midi_softc *scp;
	int rc = 0;

	scp = device_get_softc(dev);
	rc = mpu401_uninit(scp->mpu);
	if (rc)
		return (rc);
	if (scp->io != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, scp->io_rid,
		    scp->io);
		scp->io = NULL;
	}
	mtx_destroy(&scp->mtx);
	return (rc);
}