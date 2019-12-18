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
struct thread {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
struct agp_softc {scalar_t__ as_state; scalar_t__ as_isopen; int /*<<< orphan*/  as_memory; } ;
struct agp_memory {scalar_t__ am_is_bound; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AGP_ACQUIRE_USER ; 
 int /*<<< orphan*/  AGP_FREE_MEMORY (int /*<<< orphan*/ ,struct agp_memory*) ; 
 int /*<<< orphan*/  AGP_UNBIND_MEMORY (int /*<<< orphan*/ ,struct agp_memory*) ; 
 struct agp_memory* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  agp_release_helper (int /*<<< orphan*/ ,scalar_t__) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_close(struct cdev *kdev, int fflag, int devtype, struct thread *td)
{
	device_t dev = kdev->si_drv1;
	struct agp_softc *sc = device_get_softc(dev);
	struct agp_memory *mem;

	/*
	 * Clear the GATT and force release on last close
	 */
	while ((mem = TAILQ_FIRST(&sc->as_memory)) != NULL) {
		if (mem->am_is_bound)
			AGP_UNBIND_MEMORY(dev, mem);
		AGP_FREE_MEMORY(dev, mem);
	}
	if (sc->as_state == AGP_ACQUIRE_USER)
		agp_release_helper(dev, AGP_ACQUIRE_USER);
	sc->as_isopen = 0;
	device_unbusy(dev);

	return 0;
}