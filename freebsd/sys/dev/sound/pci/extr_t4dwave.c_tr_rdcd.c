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
typedef  void* u_int32_t ;
struct tr_info {int type; int rev; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  ALI_PCI_ID 131 
 int SPA_CDC_RWSTAT ; 
#define  SPA_PCI_ID 130 
 int SPA_REG_CODECRD ; 
 int TDX_CDC_RWSTAT ; 
#define  TDX_PCI_ID 129 
 int TDX_REG_CODECRD ; 
 int TDX_REG_CODECWR ; 
 int TNX_CDC_RWSTAT ; 
#define  TNX_PCI_ID 128 
 int TNX_REG_CODEC1RD ; 
 int TNX_REG_CODEC2RD ; 
 int TR_CDC_DATA ; 
 int TR_TIMEOUT_CDC ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 void* tr_rd (struct tr_info*,int,int) ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,int,int,int) ; 

__attribute__((used)) static int
tr_rdcd(kobj_t obj, void *devinfo, int regno)
{
	struct tr_info *tr = (struct tr_info *)devinfo;
	int i, j, treg, trw;

	switch (tr->type) {
	case SPA_PCI_ID:
		treg=SPA_REG_CODECRD;
		trw=SPA_CDC_RWSTAT;
		break;
	case ALI_PCI_ID:
		if (tr->rev > 0x01)
		  treg=TDX_REG_CODECWR;
		else
		  treg=TDX_REG_CODECRD;
		trw=TDX_CDC_RWSTAT;
		break;
	case TDX_PCI_ID:
		treg=TDX_REG_CODECRD;
		trw=TDX_CDC_RWSTAT;
		break;
	case TNX_PCI_ID:
		treg=(regno & 0x100)? TNX_REG_CODEC2RD : TNX_REG_CODEC1RD;
		trw=TNX_CDC_RWSTAT;
		break;
	default:
		printf("!!! tr_rdcd defaulted !!!\n");
		return -1;
	}

	i = j = 0;

	regno &= 0x7f;
	snd_mtxlock(tr->lock);
	if (tr->type == ALI_PCI_ID) {
		u_int32_t chk1, chk2;
		j = trw;
		for (i = TR_TIMEOUT_CDC; (i > 0) && (j & trw); i--)
			j = tr_rd(tr, treg, 4);
		if (i > 0) {
			chk1 = tr_rd(tr, 0xc8, 4);
			chk2 = tr_rd(tr, 0xc8, 4);
			for (i = TR_TIMEOUT_CDC; (i > 0) && (chk1 == chk2);
					i--)
				chk2 = tr_rd(tr, 0xc8, 4);
		}
	}
	if (tr->type != ALI_PCI_ID || i > 0) {
		tr_wr(tr, treg, regno | trw, 4);
		j=trw;
		for (i=TR_TIMEOUT_CDC; (i > 0) && (j & trw); i--)
		       	j=tr_rd(tr, treg, 4);
	}
	snd_mtxunlock(tr->lock);
	if (i == 0) printf("codec timeout during read of register %x\n", regno);
	return (j >> TR_CDC_DATA) & 0xffff;
}