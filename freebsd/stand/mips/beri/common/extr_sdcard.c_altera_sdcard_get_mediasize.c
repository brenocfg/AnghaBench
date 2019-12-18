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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 size_t ALTERA_SDCARD_CSD_C_SIZE_BYTE0 ; 
 size_t ALTERA_SDCARD_CSD_C_SIZE_BYTE1 ; 
 size_t ALTERA_SDCARD_CSD_C_SIZE_BYTE2 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_LSHIFT1 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_LSHIFT2 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_MASK0 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_MASK2 ; 
 size_t ALTERA_SDCARD_CSD_C_SIZE_MULT_BYTE0 ; 
 size_t ALTERA_SDCARD_CSD_C_SIZE_MULT_BYTE1 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_MULT_LSHIFT1 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_MULT_MASK0 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_MULT_MASK1 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_MULT_RSHIFT0 ; 
 int ALTERA_SDCARD_CSD_C_SIZE_RSHIFT0 ; 
 size_t ALTERA_SDCARD_CSD_READ_BL_LEN_BYTE ; 
 int ALTERA_SDCARD_CSD_READ_BL_LEN_MASK ; 
 int ALTERA_SDCARD_CSD_SIZE ; 
 int /*<<< orphan*/  altera_sdcard_read_csd (int /*<<< orphan*/ *) ; 

uint64_t
altera_sdcard_get_mediasize(void)
{
	uint64_t mediasize;
	uint64_t c_size, c_size_mult, read_bl_len;
	uint16_t csd16[ALTERA_SDCARD_CSD_SIZE/sizeof(uint16_t)];
	uint8_t *csd8p = (uint8_t *)&csd16;
	uint8_t byte0, byte1, byte2;

	altera_sdcard_read_csd(csd16);		/* Provide 16-bit alignment. */

	read_bl_len = csd8p[ALTERA_SDCARD_CSD_READ_BL_LEN_BYTE];
	read_bl_len &= ALTERA_SDCARD_CSD_READ_BL_LEN_MASK;

	byte0 = csd8p[ALTERA_SDCARD_CSD_C_SIZE_BYTE0];
	byte0 &= ALTERA_SDCARD_CSD_C_SIZE_MASK0;
	byte1 = csd8p[ALTERA_SDCARD_CSD_C_SIZE_BYTE1];
	byte2 = csd8p[ALTERA_SDCARD_CSD_C_SIZE_BYTE2];
	byte2 &= ALTERA_SDCARD_CSD_C_SIZE_MASK2;
	c_size = (byte0 >> ALTERA_SDCARD_CSD_C_SIZE_RSHIFT0) |
	    (byte1 << ALTERA_SDCARD_CSD_C_SIZE_LSHIFT1) |
	    (byte2 << ALTERA_SDCARD_CSD_C_SIZE_LSHIFT2);

	byte0 = csd8p[ALTERA_SDCARD_CSD_C_SIZE_MULT_BYTE0];
	byte0 &= ALTERA_SDCARD_CSD_C_SIZE_MULT_MASK0;
	byte1 = csd8p[ALTERA_SDCARD_CSD_C_SIZE_MULT_BYTE1];
	byte1 &= ALTERA_SDCARD_CSD_C_SIZE_MULT_MASK1;
	c_size_mult = (byte0 >> ALTERA_SDCARD_CSD_C_SIZE_MULT_RSHIFT0) |
	    (byte1 << ALTERA_SDCARD_CSD_C_SIZE_MULT_LSHIFT1);

	mediasize = (c_size + 1) * (1 << (c_size_mult + 2)) *
	    (1 << read_bl_len);
	return (mediasize);
}