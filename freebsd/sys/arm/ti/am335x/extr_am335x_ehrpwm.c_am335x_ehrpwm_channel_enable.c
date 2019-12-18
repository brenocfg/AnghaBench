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
typedef  int /*<<< orphan*/  u_int ;
struct am335x_ehrpwm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NUM_CHANNELS ; 
 int /*<<< orphan*/  PWM_LOCK (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  PWM_UNLOCK (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  am335x_ehrpwm_cfg_enable (struct am335x_ehrpwm_softc*,int /*<<< orphan*/ ,int) ; 
 struct am335x_ehrpwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_ehrpwm_channel_enable(device_t dev, u_int channel, bool enable)
{
	struct am335x_ehrpwm_softc *sc;

	if (channel >= NUM_CHANNELS)
		return (EINVAL);

	sc = device_get_softc(dev);

	PWM_LOCK(sc);
	am335x_ehrpwm_cfg_enable(sc, channel, enable);
	PWM_UNLOCK(sc);

	return (0);
}