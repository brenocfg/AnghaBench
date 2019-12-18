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
struct via_info {int /*<<< orphan*/  lock; } ;
struct via_dma_op {int dummy; } ;
struct via_chinfo {int sgd_addr; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  base; struct via_dma_op* sgd_table; struct via_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int VIA_RPCTRL_START ; 
 int VIA_RPCTRL_TERMINATE ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_buildsgdt (struct via_chinfo*) ; 
 int /*<<< orphan*/  via_wr (struct via_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
viachan_trigger(kobj_t obj, void *data, int go)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;
	struct via_dma_op *ado;
	bus_addr_t sgd_addr = ch->sgd_addr;

	if (!PCMTRIG_COMMON(go))
		return 0;

	ado = ch->sgd_table;
	DEB(printf("ado located at va=%p pa=%x\n", ado, sgd_addr));

	snd_mtxlock(via->lock);
	if (go == PCMTRIG_START) {
		via_buildsgdt(ch);
		via_wr(via, ch->base, sgd_addr, 4);
		via_wr(via, ch->ctrl, VIA_RPCTRL_START, 1);
	} else
		via_wr(via, ch->ctrl, VIA_RPCTRL_TERMINATE, 1);
	snd_mtxunlock(via->lock);

	DEB(printf("viachan_trigger: go=%d\n", go));
	return 0;
}