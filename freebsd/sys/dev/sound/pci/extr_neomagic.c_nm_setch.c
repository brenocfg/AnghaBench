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
typedef  int u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct sc_info {int dummy; } ;
struct sc_chinfo {int spd; int fmt; int /*<<< orphan*/  dir; struct sc_info* parent; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 
 scalar_t__ NM_PLAYBACK_REG_OFFSET ; 
 int NM_RATE_BITS_16 ; 
 int NM_RATE_MASK ; 
 scalar_t__ NM_RATE_REG_OFFSET ; 
 int NM_RATE_STEREO ; 
 scalar_t__ NM_RECORD_REG_OFFSET ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  nm_loadcoeff (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nm_wr (struct sc_info*,scalar_t__,int,int) ; 
 int* samplerates ; 

__attribute__((used)) static int
nm_setch(struct sc_chinfo *ch)
{
	struct sc_info *sc = ch->parent;
	u_int32_t base;
	u_int8_t x;

	for (x = 0; x < 8; x++)
		if (ch->spd < (samplerates[x] + samplerates[x + 1]) / 2)
			break;

	if (x == 8) return 1;

	ch->spd = samplerates[x];
	nm_loadcoeff(sc, ch->dir, x);

	x <<= 4;
	x &= NM_RATE_MASK;
	if (ch->fmt & AFMT_16BIT) x |= NM_RATE_BITS_16;
	if (AFMT_CHANNEL(ch->fmt) > 1) x |= NM_RATE_STEREO;

	base = (ch->dir == PCMDIR_PLAY)? NM_PLAYBACK_REG_OFFSET : NM_RECORD_REG_OFFSET;
	nm_wr(sc, base + NM_RATE_REG_OFFSET, x, 1);
	return 0;
}