#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_softc {TYPE_1__* xlat_reg; } ;
typedef  enum ntb_bar { ____Placeholder_ntb_bar } ntb_bar ;
struct TYPE_2__ {int /*<<< orphan*/  bar5_xlat; int /*<<< orphan*/  bar5_limit; int /*<<< orphan*/  bar5_base; int /*<<< orphan*/  bar4_xlat; int /*<<< orphan*/  bar4_limit; int /*<<< orphan*/  bar4_base; int /*<<< orphan*/  bar2_xlat; int /*<<< orphan*/  bar2_limit; int /*<<< orphan*/  bar2_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  NTB_B2B_BAR_1 130 
#define  NTB_B2B_BAR_2 129 
#define  NTB_B2B_BAR_3 128 
 int NTB_MAX_BARS ; 

__attribute__((used)) static inline void
bar_get_xlat_params(struct ntb_softc *ntb, enum ntb_bar bar, uint32_t *base,
    uint32_t *xlat, uint32_t *lmt)
{
	uint32_t basev, lmtv, xlatv;

	switch (bar) {
	case NTB_B2B_BAR_1:
		basev = ntb->xlat_reg->bar2_base;
		lmtv = ntb->xlat_reg->bar2_limit;
		xlatv = ntb->xlat_reg->bar2_xlat;
		break;
	case NTB_B2B_BAR_2:
		basev = ntb->xlat_reg->bar4_base;
		lmtv = ntb->xlat_reg->bar4_limit;
		xlatv = ntb->xlat_reg->bar4_xlat;
		break;
	case NTB_B2B_BAR_3:
		basev = ntb->xlat_reg->bar5_base;
		lmtv = ntb->xlat_reg->bar5_limit;
		xlatv = ntb->xlat_reg->bar5_xlat;
		break;
	default:
		KASSERT(bar >= NTB_B2B_BAR_1 && bar < NTB_MAX_BARS,
		    ("bad bar"));
		basev = lmtv = xlatv = 0;
		break;
	}

	if (base != NULL)
		*base = basev;
	if (xlat != NULL)
		*xlat = xlatv;
	if (lmt != NULL)
		*lmt = lmtv;
}