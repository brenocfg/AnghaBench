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
typedef  int u_long ;
struct thread {int dummy; } ;
struct pwmc_softc {int /*<<< orphan*/  chan; int /*<<< orphan*/  dev; } ;
struct pwm_state {int /*<<< orphan*/  enable; int /*<<< orphan*/  duty; int /*<<< orphan*/  period; } ;
struct cdev {struct pwmc_softc* si_drv1; } ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  device_t ;
typedef  struct pwm_state* caddr_t ;

/* Variables and functions */
 int PWMBUS_CHANNEL_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PWMBUS_CHANNEL_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PWMBUS_CHANNEL_GET_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PWMBUS_CHANNEL_IS_ENABLED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  PWMGETSTATE 129 
#define  PWMSETSTATE 128 
 int /*<<< orphan*/  bcopy (struct pwm_state*,struct pwm_state*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pwm_ioctl(struct cdev *dev, u_long cmd, caddr_t data,
    int fflag, struct thread *td)
{
	struct pwmc_softc *sc;
	struct pwm_state state;
	device_t bus;
	int rv = 0;

	sc = dev->si_drv1;
	bus = device_get_parent(sc->dev);

	switch (cmd) {
	case PWMSETSTATE:
		bcopy(data, &state, sizeof(state));
		rv = PWMBUS_CHANNEL_CONFIG(bus, sc->chan,
		    state.period, state.duty);
		if (rv == 0)
			rv = PWMBUS_CHANNEL_ENABLE(bus, sc->chan,
			    state.enable);
		break;
	case PWMGETSTATE:
		bcopy(data, &state, sizeof(state));
		rv = PWMBUS_CHANNEL_GET_CONFIG(bus, sc->chan,
		    &state.period, &state.duty);
		if (rv != 0)
			return (rv);
		rv = PWMBUS_CHANNEL_IS_ENABLED(bus, sc->chan,
		    &state.enable);
		if (rv != 0)
			return (rv);
		bcopy(&state, data, sizeof(state));
		break;
	}

	return (rv);
}