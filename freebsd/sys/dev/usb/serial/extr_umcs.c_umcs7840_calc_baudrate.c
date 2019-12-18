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
typedef  int usb_error_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int MCS7840_DEV_SPx_CLOCK_SHIFT ; 
 int* umcs7840_baudrate_divisors ; 
 int umcs7840_baudrate_divisors_len ; 

__attribute__((used)) static usb_error_t
umcs7840_calc_baudrate(uint32_t rate, uint16_t *divisor, uint8_t *clk)
{
	uint8_t i = 0;

	if (rate > umcs7840_baudrate_divisors[umcs7840_baudrate_divisors_len - 1])
		return (-1);

	for (i = 0; i < umcs7840_baudrate_divisors_len - 1 &&
	    !(rate > umcs7840_baudrate_divisors[i] && rate <= umcs7840_baudrate_divisors[i + 1]); ++i);
	if (rate == 0)
		*divisor = 1;	/* XXX */
	else
		*divisor = umcs7840_baudrate_divisors[i + 1] / rate;
	/* 0x00 .. 0x70 */
	*clk = i << MCS7840_DEV_SPx_CLOCK_SHIFT;
	return (0);
}