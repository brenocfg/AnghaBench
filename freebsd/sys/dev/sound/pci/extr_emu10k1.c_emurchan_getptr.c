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
typedef  int u_int32_t ;
struct sc_rchinfo {int /*<<< orphan*/  idxreg; struct sc_info* parent; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int emu_rdptr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
emurchan_getptr(kobj_t obj, void *data)
{
	struct sc_rchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	int r;

	snd_mtxlock(sc->lock);
	r = emu_rdptr(sc, 0, ch->idxreg) & 0x0000ffff;
	snd_mtxunlock(sc->lock);

	return r;
}