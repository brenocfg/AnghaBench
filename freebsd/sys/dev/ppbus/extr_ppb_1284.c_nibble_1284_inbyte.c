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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AUTOFEED ; 
 int /*<<< orphan*/  PPB_TIMEOUT ; 
 int SELECTIN ; 
 int STROBE ; 
 int do_1284_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nACK ; 
 int nINIT ; 
 int nibble2char (char) ; 
 int /*<<< orphan*/  ppb_1284_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 

int
nibble_1284_inbyte(device_t bus, char *buffer)
{
	char nibble[2];
	int i, error;

	for (i = 0; i < 2; i++) {

		/* Event 7 - ready to take data (nAUTO low) */
		ppb_wctr(bus, (nINIT | AUTOFEED) & ~(STROBE | SELECTIN));

		/* Event 8 - peripheral writes the first nibble */

		/* Event 9 - peripheral set nAck low */
		if ((error = do_1284_wait(bus, nACK, 0))) {
			ppb_1284_set_error(bus, PPB_TIMEOUT, 9);
			goto error;
		}

		/* read nibble */
		nibble[i] = ppb_rstr(bus);

		/* Event 10 - ack, nibble received */
		ppb_wctr(bus, nINIT & ~(AUTOFEED | STROBE | SELECTIN));

		/* Event 11 - wait ack from peripherial */
		if ((error = do_1284_wait(bus, nACK, nACK))) {
			ppb_1284_set_error(bus, PPB_TIMEOUT, 11);
			goto error;
		}
	}

	*buffer = ((nibble2char(nibble[1]) << 4) & 0xf0) |
				(nibble2char(nibble[0]) & 0x0f);

error:
	return (error);
}