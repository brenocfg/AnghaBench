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
struct sc_info {int dummy; } ;
struct emu_voice {int start; int /*<<< orphan*/  vnum; scalar_t__ stereo; scalar_t__ b16; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_CHAN_CCCA_CURRADDR ; 
 int emu_rdptr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_vpos(struct sc_info *sc, struct emu_voice *v)
{
	int s, ptr;

	s = (v->b16 ? 1 : 0) + (v->stereo ? 1 : 0);
	ptr = (emu_rdptr(sc, v->vnum, EMU_CHAN_CCCA_CURRADDR) - (v->start >> s)) << s;
	return ptr & ~0x0000001f;
}