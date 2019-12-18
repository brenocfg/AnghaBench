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
typedef  size_t u_int ;
struct am335x_ehrpwm_softc {TYPE_1__* sc_channels; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NUM_CHANNELS ; 
 struct am335x_ehrpwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_ehrpwm_channel_is_enabled(device_t dev, u_int channel, bool *enabled)
{
	struct am335x_ehrpwm_softc *sc;

	if (channel >= NUM_CHANNELS)
		return (EINVAL);

	sc = device_get_softc(dev);

	*enabled = sc->sc_channels[channel].enabled;

	return (0);
}