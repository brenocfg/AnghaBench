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
struct cfi_disk_softc {int flags; int /*<<< orphan*/  qlock; int /*<<< orphan*/  disk; int /*<<< orphan*/  tq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CFI_DISK_OPEN ; 
 int EBUSY ; 
 struct cfi_disk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfi_disk_detach(device_t dev)
{
	struct cfi_disk_softc *sc = device_get_softc(dev);

	if (sc->flags & CFI_DISK_OPEN)
		return EBUSY;
	taskqueue_free(sc->tq);
	/* XXX drain bioq */
	disk_destroy(sc->disk);
	mtx_destroy(&sc->qlock);
	return 0;
}