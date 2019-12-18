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

/* Variables and functions */
 char* itoa64 ; 

void
b64_from_24bit(uint8_t B2, uint8_t B1, uint8_t B0, int n, char **cp)
{
	uint32_t w;
	int i;

	w = (B2 << 16) | (B1 << 8) | B0;
	for (i = 0; i < n; i++) {
		**cp = itoa64[w&0x3f];
		(*cp)++;
		w >>= 6;
	}
}