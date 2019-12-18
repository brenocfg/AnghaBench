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
struct sc_info {int pbanksize; scalar_t__ pbankbase; int /*<<< orphan*/ * pbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrl (struct sc_info*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
ds_enapslot(struct sc_info *sc, int slot, int go)
{
	wrl(sc, &sc->pbase[slot + 1], go? (sc->pbankbase + 2 * slot * sc->pbanksize) : 0);
	/* printf("pbase[%d] = 0x%x\n", slot + 1, go? (sc->pbankbase + 2 * slot * sc->pbanksize) : 0); */
}