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
struct tr_rchinfo {int active; int /*<<< orphan*/  buffer; struct tr_info* parent; } ;
struct tr_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  TR_REG_DMAR0 ; 
 int /*<<< orphan*/  TR_REG_DMAR11 ; 
 int /*<<< orphan*/  TR_REG_DMAR15 ; 
 int /*<<< orphan*/  TR_REG_DMAR4 ; 
 int /*<<< orphan*/  TR_REG_SBCTRL ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_runsz (int /*<<< orphan*/ ) ; 
 int tr_rd (struct tr_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
trrchan_trigger(kobj_t obj, void *data, int go)
{
	struct tr_rchinfo *ch = data;
	struct tr_info *tr = ch->parent;
	u_int32_t i;

	if (!PCMTRIG_COMMON(go))
		return 0;

	if (go == PCMTRIG_START) {
		/* set up dma mode regs */
		tr_wr(tr, TR_REG_DMAR15, 0, 1);
		i = tr_rd(tr, TR_REG_DMAR11, 1) & 0x03;
		tr_wr(tr, TR_REG_DMAR11, i | 0x54, 1);
		/* set up base address */
	   	tr_wr(tr, TR_REG_DMAR0, sndbuf_getbufaddr(ch->buffer), 4);
		/* set up buffer size */
		i = tr_rd(tr, TR_REG_DMAR4, 4) & ~0x00ffffff;
		tr_wr(tr, TR_REG_DMAR4, i | (sndbuf_runsz(ch->buffer) - 1), 4);
		/* start */
		tr_wr(tr, TR_REG_SBCTRL, tr_rd(tr, TR_REG_SBCTRL, 1) | 1, 1);
		ch->active = 1;
	} else {
		tr_wr(tr, TR_REG_SBCTRL, tr_rd(tr, TR_REG_SBCTRL, 1) & ~7, 1);
		ch->active = 0;
	}

	/* return 0 if ok */
	return 0;
}