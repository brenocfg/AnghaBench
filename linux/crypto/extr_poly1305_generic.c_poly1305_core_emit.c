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
typedef  int u32 ;
struct poly1305_state {int* h; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_le32 (int,void*) ; 

void poly1305_core_emit(const struct poly1305_state *state, void *dst)
{
	u32 h0, h1, h2, h3, h4;
	u32 g0, g1, g2, g3, g4;
	u32 mask;

	/* fully carry h */
	h0 = state->h[0];
	h1 = state->h[1];
	h2 = state->h[2];
	h3 = state->h[3];
	h4 = state->h[4];

	h2 += (h1 >> 26);     h1 = h1 & 0x3ffffff;
	h3 += (h2 >> 26);     h2 = h2 & 0x3ffffff;
	h4 += (h3 >> 26);     h3 = h3 & 0x3ffffff;
	h0 += (h4 >> 26) * 5; h4 = h4 & 0x3ffffff;
	h1 += (h0 >> 26);     h0 = h0 & 0x3ffffff;

	/* compute h + -p */
	g0 = h0 + 5;
	g1 = h1 + (g0 >> 26);             g0 &= 0x3ffffff;
	g2 = h2 + (g1 >> 26);             g1 &= 0x3ffffff;
	g3 = h3 + (g2 >> 26);             g2 &= 0x3ffffff;
	g4 = h4 + (g3 >> 26) - (1 << 26); g3 &= 0x3ffffff;

	/* select h if h < p, or h + -p if h >= p */
	mask = (g4 >> ((sizeof(u32) * 8) - 1)) - 1;
	g0 &= mask;
	g1 &= mask;
	g2 &= mask;
	g3 &= mask;
	g4 &= mask;
	mask = ~mask;
	h0 = (h0 & mask) | g0;
	h1 = (h1 & mask) | g1;
	h2 = (h2 & mask) | g2;
	h3 = (h3 & mask) | g3;
	h4 = (h4 & mask) | g4;

	/* h = h % (2^128) */
	put_unaligned_le32((h0 >>  0) | (h1 << 26), dst +  0);
	put_unaligned_le32((h1 >>  6) | (h2 << 20), dst +  4);
	put_unaligned_le32((h2 >> 12) | (h3 << 14), dst +  8);
	put_unaligned_le32((h3 >> 18) | (h4 <<  8), dst + 12);
}