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
struct cyapa_softc {int poll_thread_running; scalar_t__ count; int /*<<< orphan*/  poll_ticks; int /*<<< orphan*/  dev; int /*<<< orphan*/  detaching; } ;
struct cyapa_regs {int stat; } ;
typedef  int /*<<< orphan*/  regs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEV_STATUS ; 
#define  CMD_POWER_MODE_FULL 130 
#define  CMD_POWER_MODE_IDLE 129 
#define  CMD_POWER_MODE_OFF 128 
 int CYAPA_STAT_RUNNING ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 unsigned int TIME_TO_RESET ; 
 scalar_t__ cyapa_debug ; 
 int cyapa_idle_freq ; 
 int /*<<< orphan*/  cyapa_lock (struct cyapa_softc*) ; 
 int cyapa_norm_freq ; 
 int cyapa_raw_input (struct cyapa_softc*,struct cyapa_regs*,int) ; 
 int cyapa_read_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ cyapa_reset ; 
 int /*<<< orphan*/  cyapa_set_power_mode (struct cyapa_softc*,int) ; 
 int cyapa_slow_freq ; 
 int /*<<< orphan*/  cyapa_unlock (struct cyapa_softc*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int ticks ; 

__attribute__((used)) static void
cyapa_poll_thread(void *arg)
{
	struct cyapa_softc *sc;
	struct cyapa_regs regs;
	device_t bus;		/* iicbus */
	int error;
	int freq;
	int isidle;
	int pstate;
	int npstate;
	int last_reset;

	sc = arg;
	freq = cyapa_norm_freq;
	isidle = 0;
	pstate = CMD_POWER_MODE_IDLE;
	last_reset = ticks;

	bus = device_get_parent(sc->dev);

	cyapa_lock(sc);
	sc->poll_thread_running = 1;

	while (!sc->detaching) {
		cyapa_unlock(sc);
		error = iicbus_request_bus(bus, sc->dev, IIC_WAIT);
		if (error == 0) {
			error = cyapa_read_bytes(sc->dev, CMD_DEV_STATUS,
			    (void *)&regs, sizeof(regs));
			if (error == 0) {
				isidle = cyapa_raw_input(sc, &regs, freq);
			}

			/*
			 * For some reason the device can crap-out.  If it
			 * drops back into bootstrap mode try to reinitialize
			 * it.
			 */
			if (cyapa_reset ||
			    ((regs.stat & CYAPA_STAT_RUNNING) == 0 &&
			     (unsigned)(ticks - last_reset) > TIME_TO_RESET)) {
				cyapa_reset = 0;
				last_reset = ticks;
				init_device(sc->dev, NULL, 2);
			}
			iicbus_release_bus(bus, sc->dev);
		}
		pause("cyapw", hz / freq);
		++sc->poll_ticks;

		if (sc->count == 0) {
			freq = cyapa_idle_freq;
			npstate = CMD_POWER_MODE_IDLE;
		} else if (isidle) {
			freq = cyapa_slow_freq;
			npstate = CMD_POWER_MODE_IDLE;
		} else {
			freq = cyapa_norm_freq;
			npstate = CMD_POWER_MODE_FULL;
		}
		if (pstate != npstate) {
			pstate = npstate;
			cyapa_set_power_mode(sc, pstate);
			if (cyapa_debug) {
				switch(pstate) {
				case CMD_POWER_MODE_OFF:
					printf("cyapa: power off\n");
					break;
				case CMD_POWER_MODE_IDLE:
					printf("cyapa: power idle\n");
					break;
				case CMD_POWER_MODE_FULL:
					printf("cyapa: power full\n");
					break;
				}
			}
		}

		cyapa_lock(sc);
	}
	sc->poll_thread_running = 0;
	cyapa_unlock(sc);
	kthread_exit();
}