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
typedef  int byte ;

/* Variables and functions */

short MuLawDecode(byte uLaw) {
	signed long adjusted;
	byte exponent, mantissa;

	uLaw = ~uLaw;
	exponent = (uLaw>>4) & 0x7;
	mantissa = (uLaw&0xf) + 16;
	adjusted = (mantissa << (exponent +3)) - 128 - 4;

	return (uLaw & 0x80)? adjusted : -adjusted;
}