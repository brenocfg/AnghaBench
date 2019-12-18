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
struct vmstor_chan_props {int dummy; } ;
struct storvsc_softc {TYPE_1__* hs_drv_props; int /*<<< orphan*/  hs_chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_ringbuffer_size; } ;

/* Variables and functions */
 int hv_storvsc_channel_init (struct storvsc_softc*) ; 
 int /*<<< orphan*/  hv_storvsc_on_channel_callback ; 
 int /*<<< orphan*/  memset (struct vmstor_chan_props*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_chan_cpu_rr (int /*<<< orphan*/ ) ; 
 int vmbus_chan_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct storvsc_softc*) ; 

__attribute__((used)) static int
hv_storvsc_connect_vsp(struct storvsc_softc *sc)
{	
	int ret = 0;
	struct vmstor_chan_props props;

	memset(&props, 0, sizeof(struct vmstor_chan_props));

	/*
	 * Open the channel
	 */
	vmbus_chan_cpu_rr(sc->hs_chan);
	ret = vmbus_chan_open(
		sc->hs_chan,
		sc->hs_drv_props->drv_ringbuffer_size,
		sc->hs_drv_props->drv_ringbuffer_size,
		(void *)&props,
		sizeof(struct vmstor_chan_props),
		hv_storvsc_on_channel_callback, sc);

	if (ret != 0) {
		return ret;
	}

	ret = hv_storvsc_channel_init(sc);
	return (ret);
}