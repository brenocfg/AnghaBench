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
struct tr_info {int type; int /*<<< orphan*/  lock; } ;
struct tr_chinfo {int lba; int fmc; int rvol; int cvol; int gvsel; int pan; int vol; int ctrl; int ec; int cso; int alpha; int fms; int eso; int delta; struct tr_info* parent; } ;

/* Variables and functions */
 int ALI_MAXADDR ; 
#define  ALI_PCI_ID 131 
#define  SPA_PCI_ID 130 
#define  TDX_PCI_ID 129 
#define  TNX_PCI_ID 128 
 int TR_MAXADDR ; 
 scalar_t__ TR_REG_CHNBASE ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int tr_rd (struct tr_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  tr_selch (struct tr_chinfo*) ; 

__attribute__((used)) static void
tr_rdch(struct tr_chinfo *ch)
{
	struct tr_info *tr = ch->parent;
	u_int32_t cr[5], i;

	snd_mtxlock(tr->lock);
	tr_selch(ch);
	for (i=0; i<5; i++)
		cr[i]=tr_rd(tr, TR_REG_CHNBASE+(i<<2), 4);
	snd_mtxunlock(tr->lock);


	if (tr->type == ALI_PCI_ID)
		ch->lba=(cr[1] & ALI_MAXADDR);
	else
		ch->lba=(cr[1] & TR_MAXADDR);
	ch->fmc=	(cr[3] & 0x0000c000) >> 14;
	ch->rvol=	(cr[3] & 0x00003f80) >> 7;
	ch->cvol=	(cr[3] & 0x0000007f);
	ch->gvsel=	(cr[4] & 0x80000000) >> 31;
	ch->pan=	(cr[4] & 0x7f000000) >> 24;
	ch->vol=	(cr[4] & 0x00ff0000) >> 16;
	ch->ctrl=	(cr[4] & 0x0000f000) >> 12;
	ch->ec=		(cr[4] & 0x00000fff);
	switch(tr->type) {
	case SPA_PCI_ID:
	case ALI_PCI_ID:
	case TDX_PCI_ID:
		ch->cso=	(cr[0] & 0xffff0000) >> 16;
		ch->alpha=	(cr[0] & 0x0000fff0) >> 4;
		ch->fms=	(cr[0] & 0x0000000f);
		ch->eso=	(cr[2] & 0xffff0000) >> 16;
		ch->delta=	(cr[2] & 0x0000ffff);
		break;
	case TNX_PCI_ID:
		ch->cso=	(cr[0] & 0x00ffffff);
		ch->eso=	(cr[2] & 0x00ffffff);
		ch->delta=	((cr[2] & 0xff000000) >> 16) | ((cr[0] & 0xff000000) >> 24);
		ch->alpha=	(cr[3] & 0xfff00000) >> 20;
		ch->fms=	(cr[3] & 0x000f0000) >> 16;
		break;
	}
}