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
struct lz_range_decoder {int range; int code; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 scalar_t__ getc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
lz_rd_decode(struct lz_range_decoder *rd, int num_bits)
{
	unsigned symbol = 0;

	for (int i = num_bits; i > 0; i--) {
		rd->range >>= 1;
		symbol <<= 1;
		if (rd->code >= rd->range) {
			rd->code -= rd->range;
			symbol |= 1;
		}
		if (rd->range <= 0x00FFFFFFU) {
			rd->range <<= 8; 
			rd->code = (rd->code << 8) | (uint8_t)getc(rd->fp);
		}
	}

	return symbol;
}