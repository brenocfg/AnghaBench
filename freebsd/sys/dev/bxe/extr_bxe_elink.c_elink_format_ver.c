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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 

__attribute__((used)) static elink_status_t elink_format_ver(uint32_t num, uint8_t *str, uint16_t *len)
{
	uint8_t *str_ptr = str;
	uint32_t mask = 0xf0000000;
	uint8_t shift = 8*4;
	uint8_t digit;
	uint8_t remove_leading_zeros = 1;
	if (*len < 10) {
		/* Need more than 10chars for this format */
		*str_ptr = '\0';
		(*len)--;
		return ELINK_STATUS_ERROR;
	}
	while (shift > 0) {

		shift -= 4;
		digit = ((num & mask) >> shift);
		if (digit == 0 && remove_leading_zeros) {
			mask = mask >> 4;
			continue;
		} else if (digit < 0xa)
			*str_ptr = digit + '0';
		else
			*str_ptr = digit - 0xa + 'a';
		remove_leading_zeros = 0;
		str_ptr++;
		(*len)--;
		mask = mask >> 4;
		if (shift == 4*4) {
			*str_ptr = '.';
			str_ptr++;
			(*len)--;
			remove_leading_zeros = 1;
		}
	}
	return ELINK_STATUS_OK;
}