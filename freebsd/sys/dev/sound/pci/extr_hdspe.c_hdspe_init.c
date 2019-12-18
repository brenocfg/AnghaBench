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
struct sc_info {long long ctrl_register; int period; long long speed; int type; long long settings_register; } ;

/* Variables and functions */
#define  AIO 129 
 int ENXIO ; 
 int /*<<< orphan*/  HDSPE_CONTROL_REG ; 
 long long HDSPE_FREQ_AIO ; 
 long long HDSPE_FREQ_MASK ; 
 long long HDSPE_FREQ_MASK_DEFAULT ; 
 int /*<<< orphan*/  HDSPE_FREQ_REG ; 
 int /*<<< orphan*/  HDSPE_SETTINGS_REG ; 
 long long HDSPE_SPEED_DEFAULT ; 
 long long HDSPM_CLOCK_MODE_MASTER ; 
#define  RAYDAT 128 
 long long hdspe_encode_latency (int) ; 
 int /*<<< orphan*/  hdspe_write_4 (struct sc_info*,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static int
hdspe_init(struct sc_info *sc)
{
	long long period;

	/* Set defaults. */
	sc->ctrl_register |= HDSPM_CLOCK_MODE_MASTER;

	/* Set latency. */
	sc->period = 32;
	sc->ctrl_register = hdspe_encode_latency(7);

	/* Set rate. */
	sc->speed = HDSPE_SPEED_DEFAULT;
	sc->ctrl_register &= ~HDSPE_FREQ_MASK;
	sc->ctrl_register |= HDSPE_FREQ_MASK_DEFAULT;
	hdspe_write_4(sc, HDSPE_CONTROL_REG, sc->ctrl_register);

	switch (sc->type) {
	case RAYDAT:
	case AIO:
		period = HDSPE_FREQ_AIO;
		break;
	default:
		return (ENXIO);
	}

	/* Set DDS value. */
	period /= sc->speed;
	hdspe_write_4(sc, HDSPE_FREQ_REG, period);

	/* Other settings. */
	sc->settings_register = 0;
	hdspe_write_4(sc, HDSPE_SETTINGS_REG, sc->settings_register);

	return (0);
}