#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ahci_enclosure {int channels; int /*<<< orphan*/  mtx; scalar_t__ r_memr; scalar_t__ r_memt; scalar_t__ r_memc; int /*<<< orphan*/  sim; int /*<<< orphan*/  path; TYPE_1__* leds; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ led; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int AHCI_NUM_LEDS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 struct ahci_enclosure* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahci_em_detach(device_t dev)
{
	struct ahci_enclosure *enc = device_get_softc(dev);
	int i;

	for (i = 0; i < enc->channels * AHCI_NUM_LEDS; i++) {
		if (enc->leds[i].led)
			led_destroy(enc->leds[i].led);
	}
	mtx_lock(&enc->mtx);
	xpt_async(AC_LOST_DEVICE, enc->path, NULL);
	xpt_free_path(enc->path);
	xpt_bus_deregister(cam_sim_path(enc->sim));
	cam_sim_free(enc->sim, /*free_devq*/TRUE);
	mtx_unlock(&enc->mtx);

	bus_release_resource(dev, SYS_RES_MEMORY, 0, enc->r_memc);
	bus_release_resource(dev, SYS_RES_MEMORY, 1, enc->r_memt);
	if (enc->r_memr)
		bus_release_resource(dev, SYS_RES_MEMORY, 2, enc->r_memr);
	mtx_destroy(&enc->mtx);
	return (0);
}