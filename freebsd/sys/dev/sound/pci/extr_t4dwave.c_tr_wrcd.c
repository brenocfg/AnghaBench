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
struct tr_info {int type; int rev; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  ALI_PCI_ID 131 
 int SPA_CDC_RWSTAT ; 
#define  SPA_PCI_ID 130 
 int SPA_REG_CODECWR ; 
 int TDX_CDC_RWSTAT ; 
#define  TDX_PCI_ID 129 
 int TDX_REG_CODECWR ; 
 int TNX_CDC_RWSTAT ; 
 int TNX_CDC_SEC ; 
#define  TNX_PCI_ID 128 
 int TNX_REG_CODECWR ; 
 int TR_CDC_DATA ; 
 int TR_TIMEOUT_CDC ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int tr_rd (struct tr_info*,int,int) ; 
 int tr_rdcd (void*,int) ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,int,int,int) ; 

__attribute__((used)) static int
tr_wrcd(kobj_t obj, void *devinfo, int regno, u_int32_t data)
{
	struct tr_info *tr = (struct tr_info *)devinfo;
	int i, j, treg, trw;

	switch (tr->type) {
	case SPA_PCI_ID:
		treg=SPA_REG_CODECWR;
		trw=SPA_CDC_RWSTAT;
		break;
	case ALI_PCI_ID:
	case TDX_PCI_ID:
		treg=TDX_REG_CODECWR;
		trw=TDX_CDC_RWSTAT;
		break;
	case TNX_PCI_ID:
		treg=TNX_REG_CODECWR;
		trw=TNX_CDC_RWSTAT | ((regno & 0x100)? TNX_CDC_SEC : 0);
		break;
	default:
		printf("!!! tr_wrcd defaulted !!!");
		return -1;
	}

	i = 0;

	regno &= 0x7f;
#if 0
	printf("tr_wrcd: reg %x was %x", regno, tr_rdcd(devinfo, regno));
#endif
	j=trw;
	snd_mtxlock(tr->lock);
	if (tr->type == ALI_PCI_ID) {
		j = trw;
		for (i = TR_TIMEOUT_CDC; (i > 0) && (j & trw); i--)
			j = tr_rd(tr, treg, 4);
		if (i > 0) {
			u_int32_t chk1, chk2;
			chk1 = tr_rd(tr, 0xc8, 4);
			chk2 = tr_rd(tr, 0xc8, 4);
			for (i = TR_TIMEOUT_CDC; (i > 0) && (chk1 == chk2);
					i--)
				chk2 = tr_rd(tr, 0xc8, 4);
		}
	}
	if (tr->type != ALI_PCI_ID || i > 0) {
		for (i=TR_TIMEOUT_CDC; (i>0) && (j & trw); i--)
			j=tr_rd(tr, treg, 4);
		if (tr->type == ALI_PCI_ID && tr->rev > 0x01)
		      	trw |= 0x0100;
		tr_wr(tr, treg, (data << TR_CDC_DATA) | regno | trw, 4);
	}
#if 0
	printf(" - wrote %x, now %x\n", data, tr_rdcd(devinfo, regno));
#endif
	snd_mtxunlock(tr->lock);
	if (i==0) printf("codec timeout writing %x, data %x\n", regno, data);
	return (i > 0)? 0 : -1;
}