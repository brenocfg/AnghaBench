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
typedef  size_t uint8_t ;
struct wpi_softc {int temp; int /*<<< orphan*/ * maxpwr; } ;
struct wpi_power_sample {int power; int /*<<< orphan*/  index; } ;
struct wpi_power_group {int maxpwr; int temp; struct wpi_power_sample* samples; } ;

/* Variables and functions */
 int WPI_MAX_PWR_INDEX ; 
 int WPI_RIDX_CCK1 ; 
#define  WPI_RIDX_OFDM36 130 
#define  WPI_RIDX_OFDM48 129 
#define  WPI_RIDX_OFDM54 128 
 int interpolate (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wpi_get_power_index(struct wpi_softc *sc, struct wpi_power_group *group,
    uint8_t chan, int is_chan_5ghz, int ridx)
{
/* Fixed-point arithmetic division using a n-bit fractional part. */
#define fdivround(a, b, n)	\
	((((1 << n) * (a)) / (b) + (1 << n) / 2) / (1 << n))

/* Linear interpolation. */
#define interpolate(x, x1, y1, x2, y2, n)	\
	((y1) + fdivround(((x) - (x1)) * ((y2) - (y1)), (x2) - (x1), n))

	struct wpi_power_sample *sample;
	int pwr, idx;

	/* Default TX power is group maximum TX power minus 3dB. */
	pwr = group->maxpwr / 2;

	/* Decrease TX power for highest OFDM rates to reduce distortion. */
	switch (ridx) {
	case WPI_RIDX_OFDM36:
		pwr -= is_chan_5ghz ?  5 : 0;
		break;
	case WPI_RIDX_OFDM48:
		pwr -= is_chan_5ghz ? 10 : 7;
		break;
	case WPI_RIDX_OFDM54:
		pwr -= is_chan_5ghz ? 12 : 9;
		break;
	}

	/* Never exceed the channel maximum allowed TX power. */
	pwr = min(pwr, sc->maxpwr[chan]);

	/* Retrieve TX power index into gain tables from samples. */
	for (sample = group->samples; sample < &group->samples[3]; sample++)
		if (pwr > sample[1].power)
			break;
	/* Fixed-point linear interpolation using a 19-bit fractional part. */
	idx = interpolate(pwr, sample[0].power, sample[0].index,
	    sample[1].power, sample[1].index, 19);

	/*-
	 * Adjust power index based on current temperature:
	 * - if cooler than factory-calibrated: decrease output power
	 * - if warmer than factory-calibrated: increase output power
	 */
	idx -= (sc->temp - group->temp) * 11 / 100;

	/* Decrease TX power for CCK rates (-5dB). */
	if (ridx >= WPI_RIDX_CCK1)
		idx += 10;

	/* Make sure idx stays in a valid range. */
	if (idx < 0)
		return 0;
	if (idx > WPI_MAX_PWR_INDEX)
		return WPI_MAX_PWR_INDEX;
	return idx;

#undef interpolate
#undef fdivround
}