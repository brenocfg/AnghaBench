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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_pchinfo {int spd; int /*<<< orphan*/  buffer; int /*<<< orphan*/  blksz; struct sc_info* parent; } ;
struct sc_info {int timerinterval; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  emu_settimer (struct sc_info*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int sndbuf_getalign (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
emupchan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	struct sc_pchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	int irqrate, blksz;

	ch->blksz = blocksize;
	snd_mtxlock(sc->lock);
	emu_settimer(sc);
	irqrate = 48000 / sc->timerinterval;
	snd_mtxunlock(sc->lock);
	blksz = (ch->spd * sndbuf_getalign(ch->buffer)) / irqrate;
	return blocksize;
}