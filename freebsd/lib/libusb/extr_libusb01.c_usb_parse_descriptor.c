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

/* Variables and functions */

int
usb_parse_descriptor(uint8_t *source, char *description, void *dest)
{
	uint8_t *sp = source;
	uint8_t *dp = dest;
	uint16_t w;
	uint32_t d;
	char *cp;

	for (cp = description; *cp; cp++) {
		switch (*cp) {
		case 'b':		/* 8-bit byte */
			*dp++ = *sp++;
			break;
			/*
			 * 16-bit word, convert from little endian to CPU
			 */
		case 'w':
			w = (sp[1] << 8) | sp[0];
			sp += 2;
			/* Align to word boundary */
			dp += ((dp - (uint8_t *)0) & 1);
			*((uint16_t *)dp) = w;
			dp += 2;
			break;
			/*
			 * 32-bit dword, convert from little endian to CPU
			 */
		case 'd':
			d = (sp[3] << 24) | (sp[2] << 16) |
			    (sp[1] << 8) | sp[0];
			sp += 4;
			/* Align to word boundary */
			dp += ((dp - (uint8_t *)0) & 1);
			/* Align to double word boundary */
			dp += ((dp - (uint8_t *)0) & 2);
			*((uint32_t *)dp) = d;
			dp += 4;
			break;
		}
	}
	return (sp - source);
}