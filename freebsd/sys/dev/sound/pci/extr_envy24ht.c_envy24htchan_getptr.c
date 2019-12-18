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
struct sc_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct sc_chinfo {int unit; int /*<<< orphan*/  dir; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int envy24ht_gethwptr (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
envy24htchan_getptr(kobj_t obj, void *data)
{
	struct sc_chinfo *ch = data;
	struct sc_info *sc = ch->parent;
	u_int32_t ptr, rtn;

#if(0)
	device_printf(sc->dev, "envy24htchan_getptr()\n");
#endif
	snd_mtxlock(sc->lock);
	ptr = envy24ht_gethwptr(sc, ch->dir);
	rtn = ptr * ch->unit;
	snd_mtxunlock(sc->lock);

#if(0)
	device_printf(sc->dev, "envy24htchan_getptr(): return %d\n",
	    rtn);
#endif
	return rtn;
}