#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; scalar_t__ device_file; scalar_t__ command_dmatag; scalar_t__ sg_dmatag; int /*<<< orphan*/  timer; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ips_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 
 int IPS_DEV_OPEN ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ips_cmdqueue_free (TYPE_1__*) ; 
 int ips_diskdev_free (TYPE_1__*) ; 

int ips_adapter_free(ips_softc_t *sc)
{
	int error = 0;
	if(sc->state & IPS_DEV_OPEN)
		return EBUSY;
	if((error = ips_diskdev_free(sc)))
		return error;
	if(ips_cmdqueue_free(sc)){
		device_printf(sc->dev,
		     "trying to exit when command queue is not empty!\n");
		return EBUSY;
	}
	DEVICE_PRINTF(1, sc->dev, "free\n");
	callout_drain(&sc->timer);

	if(sc->sg_dmatag)
		bus_dma_tag_destroy(sc->sg_dmatag);
	if(sc->command_dmatag)
		bus_dma_tag_destroy(sc->command_dmatag);
	if(sc->device_file)
	        destroy_dev(sc->device_file);
        return 0;
}