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
 int hex_digit (int) ; 

__attribute__((used)) static void
format_byte(uint8_t v, uint8_t *buf)
{

	buf[0] = hex_digit(v >> 4);
	buf[1] = hex_digit(v & 0xf);
}