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
struct tr_chinfo {int gvsel; int fmc; int fms; int ctrl; int pan; int rvol; int cvol; int vol; int ec; int alpha; int delta; int lba; int cso; int eso; struct tr_info* parent; } ;

/* Variables and functions */
 int ALI_MAXADDR ; 
#define  ALI_PCI_ID 131 
#define  SPA_PCI_ID 130 
#define  TDX_PCI_ID 129 
#define  TNX_PCI_ID 128 
 int TR_CHN_REGS ; 
 int TR_MAXADDR ; 
 scalar_t__ TR_REG_CHNBASE ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_selch (struct tr_chinfo*) ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,scalar_t__,int,int) ; 

__attribute__((used)) static void
tr_wrch(struct tr_chinfo *ch)
{
	struct tr_info *tr = ch->parent;
	u_int32_t cr[TR_CHN_REGS], i;

	ch->gvsel 	&= 0x00000001;
	ch->fmc		&= 0x00000003;
	ch->fms		&= 0x0000000f;
	ch->ctrl	&= 0x0000000f;
	ch->pan 	&= 0x0000007f;
	ch->rvol	&= 0x0000007f;
	ch->cvol 	&= 0x0000007f;
	ch->vol		&= 0x000000ff;
	ch->ec		&= 0x00000fff;
	ch->alpha	&= 0x00000fff;
	ch->delta	&= 0x0000ffff;
	if (tr->type == ALI_PCI_ID)
		ch->lba &= ALI_MAXADDR;
	else
		ch->lba &= TR_MAXADDR;

	cr[1]=ch->lba;
	cr[3]=(ch->fmc<<14) | (ch->rvol<<7) | (ch->cvol);
	cr[4]=(ch->gvsel<<31) | (ch->pan<<24) | (ch->vol<<16) | (ch->ctrl<<12) | (ch->ec);

	switch (tr->type) {
	case SPA_PCI_ID:
	case ALI_PCI_ID:
	case TDX_PCI_ID:
		ch->cso &= 0x0000ffff;
		ch->eso &= 0x0000ffff;
		cr[0]=(ch->cso<<16) | (ch->alpha<<4) | (ch->fms);
		cr[2]=(ch->eso<<16) | (ch->delta);
		break;
	case TNX_PCI_ID:
		ch->cso &= 0x00ffffff;
		ch->eso &= 0x00ffffff;
		cr[0]=((ch->delta & 0xff)<<24) | (ch->cso);
		cr[2]=((ch->delta>>8)<<24) | (ch->eso);
		cr[3]|=(ch->alpha<<20) | (ch->fms<<16) | (ch->fmc<<14);
		break;
	}
	snd_mtxlock(tr->lock);
	tr_selch(ch);
	for (i=0; i<TR_CHN_REGS; i++)
		tr_wr(tr, TR_REG_CHNBASE+(i<<2), cr[i], 4);
	snd_mtxunlock(tr->lock);
}