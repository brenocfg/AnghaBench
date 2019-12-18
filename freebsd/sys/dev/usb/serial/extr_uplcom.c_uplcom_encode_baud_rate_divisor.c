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

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,unsigned int) ; 

__attribute__((used)) static unsigned int
uplcom_encode_baud_rate_divisor(uint8_t *buf, unsigned int baud)
{
	unsigned int baseline, mantissa, exponent;

	/* Determine the baud rate divisor. This algorithm is taken from Linux. */
	/*
	 * Apparently the formula is:
	 *   baudrate = baseline / (mantissa * 4^exponent)
	 * where
	 *   mantissa = buf[8:0]
	 *   exponent = buf[11:9]
	 */
	if (baud == 0)
		baud = 1;
	baseline = 383385600;
	mantissa = baseline / baud;
	if (mantissa == 0)
		mantissa = 1;
	exponent = 0;
	while (mantissa >= 512) {
		if (exponent < 7) {
			mantissa >>= 2;	/* divide by 4 */
			exponent++;
		} else {
			/* Exponent is maxed. Trim mantissa and leave. This gives approx. 45.8 baud */
			mantissa = 511;
			break;
		}
	}

	buf[3] = 0x80;
	buf[2] = 0;
	buf[1] = exponent << 1 | mantissa >> 8;
	buf[0] = mantissa & 0xff;

	/* Calculate and return the exact baud rate. */
	baud = (baseline / mantissa) >> (exponent << 1);
	DPRINTF("real baud rate will be %u\n", baud);

	return baud;
}