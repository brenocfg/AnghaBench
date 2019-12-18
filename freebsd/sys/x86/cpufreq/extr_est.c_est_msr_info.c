#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint16_t ;
struct est_softc {int /*<<< orphan*/  msr_settings; } ;
struct TYPE_4__ {int freq; int volts; int id16; void* power; } ;
typedef  TYPE_1__ freq_info ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* CPUFREQ_VAL_UNKNOWN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TRUE ; 
 int atomic_load_acq_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_speed_ok (int) ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msr_info_enabled ; 
 int /*<<< orphan*/  tsc_freq ; 

__attribute__((used)) static int
est_msr_info(device_t dev, uint64_t msr, freq_info **freqs, size_t *freqslen)
{
	struct est_softc *sc;
	freq_info *fp;
	int bus, freq, volts;
	uint16_t id;

	if (!msr_info_enabled)
		return (EOPNOTSUPP);

	/* Figure out the bus clock. */
	freq = atomic_load_acq_64(&tsc_freq) / 1000000;
	id = msr >> 32;
	bus = freq / (id >> 8);
	device_printf(dev, "Guessed bus clock (high) of %d MHz\n", bus);
	if (!bus_speed_ok(bus)) {
		/* We may be running on the low frequency. */
		id = msr >> 48;
		bus = freq / (id >> 8);
		device_printf(dev, "Guessed bus clock (low) of %d MHz\n", bus);
		if (!bus_speed_ok(bus))
			return (EOPNOTSUPP);

		/* Calculate high frequency. */
		id = msr >> 32;
		freq = ((id >> 8) & 0xff) * bus;
	}

	/* Fill out a new freq table containing just the high and low freqs. */
	sc = device_get_softc(dev);
	fp = malloc(sizeof(freq_info) * 2, M_DEVBUF, M_WAITOK | M_ZERO);

	/* First, the high frequency. */
	volts = id & 0xff;
	if (volts != 0) {
		volts <<= 4;
		volts += 700;
	}
	fp[0].freq = freq;
	fp[0].volts = volts;
	fp[0].id16 = id;
	fp[0].power = CPUFREQ_VAL_UNKNOWN;
	device_printf(dev, "Guessed high setting of %d MHz @ %d Mv\n", freq,
	    volts);

	/* Second, the low frequency. */
	id = msr >> 48;
	freq = ((id >> 8) & 0xff) * bus;
	volts = id & 0xff;
	if (volts != 0) {
		volts <<= 4;
		volts += 700;
	}
	fp[1].freq = freq;
	fp[1].volts = volts;
	fp[1].id16 = id;
	fp[1].power = CPUFREQ_VAL_UNKNOWN;
	device_printf(dev, "Guessed low setting of %d MHz @ %d Mv\n", freq,
	    volts);

	/* Table is already terminated due to M_ZERO. */
	sc->msr_settings = TRUE;
	*freqs = fp;
	*freqslen = 2;
	return (0);
}