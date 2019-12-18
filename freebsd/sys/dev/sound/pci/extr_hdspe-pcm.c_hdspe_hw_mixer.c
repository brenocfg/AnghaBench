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
typedef  int /*<<< orphan*/  uint32_t ;
struct sc_pcminfo {struct sc_info* sc; } ;
struct sc_info {int dummy; } ;
struct sc_chinfo {scalar_t__ dir; struct sc_pcminfo* parent; } ;

/* Variables and functions */
 scalar_t__ HDSPE_MIXER_BASE ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  hdspe_write_4 (struct sc_info*,scalar_t__,unsigned short) ; 

__attribute__((used)) static int
hdspe_hw_mixer(struct sc_chinfo *ch, unsigned int dst,
    unsigned int src, unsigned short data)
{
	struct sc_pcminfo *scp;
	struct sc_info *sc;
	int offs;

	scp = ch->parent;
	sc = scp->sc;

	offs = 0;
	if (ch->dir == PCMDIR_PLAY)
		offs = 64;

	hdspe_write_4(sc, HDSPE_MIXER_BASE +
	    ((offs + src + 128 * dst) * sizeof(uint32_t)),
	    data & 0xFFFF);

	return (0);
}