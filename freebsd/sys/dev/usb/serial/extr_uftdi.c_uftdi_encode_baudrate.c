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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct uftdi_softc {int sc_devflags; scalar_t__ sc_devtype; } ;
struct uftdi_param_config {int baud_hibits; void* baud_lobits; } ;
typedef  int speed_t ;

/* Variables and functions */
 int DEVF_BAUDBITS_HINDEX ; 
 int DEVF_BAUDCLK_12M ; 
 scalar_t__ DEVT_232A ; 
 int ERANGE ; 
 int /*<<< orphan*/  uftdi_baud_within_tolerance (int,int) ; 

__attribute__((used)) static int
uftdi_encode_baudrate(struct uftdi_softc *sc, speed_t speed,
	struct uftdi_param_config *cfg)
{
	static const uint8_t encoded_fraction[8] = {0, 3, 2, 4, 1, 5, 6, 7};
	static const uint8_t roundoff_232a[16] = {
		0,  1,  0,  1,  0, -1,  2,  1,
		0, -1, -2, -3,  4,  3,  2,  1,
	};
	uint32_t clk, divisor, fastclk_flag, frac, hwspeed;

	/*
	 * If this chip has the fast clock capability and the speed is within
	 * range, use the 12MHz clock, otherwise the standard clock is 3MHz.
	 */
	if ((sc->sc_devflags & DEVF_BAUDCLK_12M) && speed >= 1200) {
		clk = 12000000;
		fastclk_flag = (1 << 17);
	} else {
		clk = 3000000;
		fastclk_flag = 0;
	}

	/*
	 * Make sure the requested speed is reachable with the available clock
	 * and a 14-bit divisor.
	 */
	if (speed < (clk >> 14) || speed > clk)
		return (ERANGE);

	/*
	 * Calculate the divisor, initially yielding a fixed point number with a
	 * 4-bit (1/16ths) fraction, then round it to the nearest fraction the
	 * hardware can handle.  When the integral part of the divisor is
	 * greater than one, the fractional part is in 1/8ths of the base clock.
	 * The FT8U232AM chips can handle only 0.125, 0.250, and 0.5 fractions.
	 * Later chips can handle all 1/8th fractions.
	 *
	 * If the integral part of the divisor is 1, a special rule applies: the
	 * fractional part can only be .0 or .5 (this is a limitation of the
	 * hardware).  We handle this by truncating the fraction rather than
	 * rounding, because this only applies to the two fastest speeds the
	 * chip can achieve and rounding doesn't matter, either you've asked for
	 * that exact speed or you've asked for something the chip can't do.
	 *
	 * For the FT8U232AM chips, use a roundoff table to adjust the result
	 * to the nearest 1/8th fraction that is supported by the hardware,
	 * leaving a fixed-point number with a 3-bit fraction which exactly
	 * represents the math the hardware divider will do.  For later-series
	 * chips that support all 8 fractional divisors, just round 16ths to
	 * 8ths by adding 1 and dividing by 2.
	 */
	divisor = (clk << 4) / speed;
	if ((divisor & 0xf) == 1)
		divisor &= 0xfffffff8;
	else if (sc->sc_devtype == DEVT_232A)
		divisor += roundoff_232a[divisor & 0x0f];
	else
		divisor += 1;  /* Rounds odd 16ths up to next 8th. */
	divisor >>= 1;

	/*
	 * Ensure the resulting hardware speed will be within operational
	 * tolerance (within 3% of nominal).
	 */
	hwspeed = (clk << 3) / divisor;
	if (!uftdi_baud_within_tolerance(hwspeed, speed))
		return (ERANGE);

	/*
	 * Re-pack the divisor into hardware format. The lower 14-bits hold the
	 * integral part, while the upper bits specify the fraction by indexing
	 * a table of fractions within the hardware which is laid out as:
	 *    {0.0, 0.5, 0.25, 0.125, 0.325, 0.625, 0.725, 0.875}
	 * The A-series chips only have the first four table entries; the
	 * roundoff table logic above ensures that the fractional part for those
	 * chips will be one of the first four values.
	 *
	 * When the divisor is 1 a special encoding applies:  1.0 is encoded as
	 * 0.0, and 1.5 is encoded as 1.0.  The rounding logic above has already
	 * ensured that the fraction is either .0 or .5 if the integral is 1.
	 */
	frac = divisor & 0x07;
	divisor >>= 3;
	if (divisor == 1) {
		if (frac == 0)
			divisor = 0;  /* 1.0 becomes 0.0 */
		else
			frac = 0;     /* 1.5 becomes 1.0 */
	}
	divisor |= (encoded_fraction[frac] << 14) | fastclk_flag;
        
	cfg->baud_lobits = (uint16_t)divisor;
	cfg->baud_hibits = (uint16_t)(divisor >> 16);

	/*
	 * If this chip requires the baud bits to be in the high byte of the
	 * index word, move the bits up to that location.
	 */
	if (sc->sc_devflags & DEVF_BAUDBITS_HINDEX) {
		cfg->baud_hibits <<= 8;
	}

	return (0);
}