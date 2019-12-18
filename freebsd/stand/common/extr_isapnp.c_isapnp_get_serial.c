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
 int /*<<< orphan*/  SERIAL_ISOLATION ; 
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 int /*<<< orphan*/  _PNP_ID_LEN ; 
 int /*<<< orphan*/  bzero (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay (int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isapnp_readport ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isapnp_get_serial(uint8_t *data)
{
    int		i, bit, valid = 0, sum = 0x6a;

    bzero(data, _PNP_ID_LEN);
    outb(_PNP_ADDRESS, SERIAL_ISOLATION);
    for (i = 0; i < 72; i++) {
	bit = inb(isapnp_readport) == 0x55;
	delay(250);	/* Delay 250 usec */

	/* Can't Short Circuit the next evaluation, so 'and' is last */
	bit = (inb(isapnp_readport) == 0xaa) && bit;
	delay(250);	/* Delay 250 usec */

	valid = valid || bit;

	if (i < 64)
	    sum = (sum >> 1) |
		(((sum ^ (sum >> 1) ^ bit) << 7) & 0xff);

	data[i / 8] = (data[i / 8] >> 1) | (bit ? 0x80 : 0);
    }

    valid = valid && (data[8] == sum);

    return valid;
}