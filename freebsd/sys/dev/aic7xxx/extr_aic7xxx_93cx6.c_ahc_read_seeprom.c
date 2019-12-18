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
typedef  int uint16_t ;
typedef  int u_int ;
struct seeprom_descriptor {int sd_MS; int sd_CS; int sd_chip; int sd_DO; int sd_CK; int sd_DI; int /*<<< orphan*/  sd_RDY; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PULSE (struct seeprom_descriptor*,int /*<<< orphan*/ ) ; 
 int SEEPROM_DATA_INB (struct seeprom_descriptor*) ; 
 int /*<<< orphan*/  SEEPROM_OUTB (struct seeprom_descriptor*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  reset_seeprom (struct seeprom_descriptor*) ; 
 int /*<<< orphan*/  seeprom_read ; 
 int /*<<< orphan*/  send_seeprom_cmd (struct seeprom_descriptor*,int /*<<< orphan*/ *) ; 

int
ahc_read_seeprom(struct seeprom_descriptor *sd, uint16_t *buf,
		 u_int start_addr, u_int count)
{
	int i = 0;
	u_int k = 0;
	uint16_t v;
	uint8_t temp;

	/*
	 * Read the requested registers of the seeprom.  The loop
	 * will range from 0 to count-1.
	 */
	for (k = start_addr; k < count + start_addr; k++) {
		/*
		 * Now we're ready to send the read command followed by the
		 * address of the 16-bit register we want to read.
		 */
		send_seeprom_cmd(sd, &seeprom_read);

		/* Send the 6 or 8 bit address (MSB first, LSB last). */
		temp = sd->sd_MS ^ sd->sd_CS;
		for (i = (sd->sd_chip - 1); i >= 0; i--) {
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		}

		/*
		 * Now read the 16 bit register.  An initial 0 precedes the
		 * register contents which begins with bit 15 (MSB) and ends
		 * with bit 0 (LSB).  The initial 0 will be shifted off the
		 * top of our word as we let the loop run from 0 to 16.
		 */
		v = 0;
		for (i = 16; i >= 0; i--) {
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			v <<= 1;
			if (SEEPROM_DATA_INB(sd) & sd->sd_DI)
				v |= 1;
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
		}

		buf[k - start_addr] = v;

		/* Reset the chip select for the next command cycle. */
		reset_seeprom(sd);
	}
#ifdef AHC_DUMP_EEPROM
	printf("\nSerial EEPROM:\n\t");
	for (k = 0; k < count; k = k + 1) {
		if (((k % 8) == 0) && (k != 0)) {
			printf ("\n\t");
		}
		printf (" 0x%x", buf[k]);
	}
	printf ("\n");
#endif
	return (1);
}