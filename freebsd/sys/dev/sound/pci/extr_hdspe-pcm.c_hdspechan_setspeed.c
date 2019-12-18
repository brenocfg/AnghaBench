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
typedef  int uint32_t ;
struct sc_pcminfo {int /*<<< orphan*/  dev; struct sc_info* sc; } ;
struct sc_info {int type; long long ctrl_register; int speed; } ;
struct sc_chinfo {struct sc_pcminfo* parent; } ;
struct hdspe_rate {int speed; long long reg; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  AIO 129 
 int /*<<< orphan*/  HDSPE_CONTROL_REG ; 
 long long HDSPE_FREQ_AIO ; 
 long long HDSPE_FREQ_MASK ; 
 int /*<<< orphan*/  HDSPE_FREQ_REG ; 
#define  RAYDAT 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int hdspe_running (struct sc_info*) ; 
 int /*<<< orphan*/  hdspe_write_4 (struct sc_info*,int /*<<< orphan*/ ,long long) ; 
 struct hdspe_rate* rate_map ; 

__attribute__((used)) static uint32_t
hdspechan_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct sc_pcminfo *scp;
	struct hdspe_rate *hr;
	struct sc_chinfo *ch;
	struct sc_info *sc;
	long long period;
	int threshold;
	int i;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;
	hr = NULL;

#if 0
	device_printf(scp->dev, "hdspechan_setspeed(%d)\n", speed);
#endif

	if (hdspe_running(sc) == 1)
		goto end;

	/* First look for equal frequency. */
	for (i = 0; rate_map[i].speed != 0; i++) {
		if (rate_map[i].speed == speed)
			hr = &rate_map[i];
	}

	/* If no match, just find nearest. */
	if (hr == NULL) {
		for (i = 0; rate_map[i].speed != 0; i++) {
			hr = &rate_map[i];
			threshold = hr->speed + ((rate_map[i + 1].speed != 0) ?
			    ((rate_map[i + 1].speed - hr->speed) >> 1) : 0);
			if (speed < threshold)
				break;
		}
	}

	switch (sc->type) {
	case RAYDAT:
	case AIO:
		period = HDSPE_FREQ_AIO;
		break;
	default:
		/* Unsupported card. */
		goto end;
	}

	/* Write frequency on the device. */
	sc->ctrl_register &= ~HDSPE_FREQ_MASK;
	sc->ctrl_register |= hr->reg;
	hdspe_write_4(sc, HDSPE_CONTROL_REG, sc->ctrl_register);

	speed = hr->speed;
	if (speed > 96000)
		speed /= 4;
	else if (speed > 48000)
		speed /= 2;

	/* Set DDS value. */
	period /= speed;
	hdspe_write_4(sc, HDSPE_FREQ_REG, period);

	sc->speed = hr->speed;
end:

	return (sc->speed);
}