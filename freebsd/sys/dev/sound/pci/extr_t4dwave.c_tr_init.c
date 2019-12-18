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
struct tr_info {int type; } ;

/* Variables and functions */
#define  SPA_PCI_ID 130 
 int /*<<< orphan*/  SPA_REG_CODECST ; 
 int /*<<< orphan*/  SPA_REG_GPIO ; 
 int SPA_RST_OFF ; 
 int TDX_CDC_ON ; 
#define  TDX_PCI_ID 129 
 int /*<<< orphan*/  TDX_REG_CODECST ; 
 int TNX_CDC_ON ; 
#define  TNX_PCI_ID 128 
 int /*<<< orphan*/  TNX_REG_CODECST ; 
 int TR_CIR_ADDRENA ; 
 int TR_CIR_MIDENA ; 
 int /*<<< orphan*/  TR_REG_CIR ; 
 int /*<<< orphan*/  tr_wr (struct tr_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
tr_init(struct tr_info *tr)
{
	switch (tr->type) {
	case SPA_PCI_ID:
		tr_wr(tr, SPA_REG_GPIO, 0, 4);
		tr_wr(tr, SPA_REG_CODECST, SPA_RST_OFF, 4);
		break;
	case TDX_PCI_ID:
		tr_wr(tr, TDX_REG_CODECST, TDX_CDC_ON, 4);
		break;
	case TNX_PCI_ID:
		tr_wr(tr, TNX_REG_CODECST, TNX_CDC_ON, 4);
		break;
	}

	tr_wr(tr, TR_REG_CIR, TR_CIR_MIDENA | TR_CIR_ADDRENA, 4);
	return 0;
}