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
struct he_dev {TYPE_1__* atm_dev; } ;
struct TYPE_2__ {unsigned int link_rate; } ;

/* Variables and functions */
 scalar_t__ CS_ERCTL0 ; 
 scalar_t__ CS_ERCTL1 ; 
 scalar_t__ CS_ERCTL2 ; 
 scalar_t__ CS_ERSTAT0 ; 
 scalar_t__ CS_ERSTAT1 ; 
 scalar_t__ CS_ERTHR0 ; 
 scalar_t__ CS_ERTHR1 ; 
 scalar_t__ CS_ERTHR2 ; 
 scalar_t__ CS_ERTHR3 ; 
 scalar_t__ CS_ERTHR4 ; 
 scalar_t__ CS_HGRRT0 ; 
 scalar_t__ CS_OTPPER ; 
 scalar_t__ CS_OTTLIM ; 
 scalar_t__ CS_OTWPER ; 
 scalar_t__ CS_RTATR ; 
 scalar_t__ CS_RTFWR ; 
 scalar_t__ CS_STTIM0 ; 
 scalar_t__ CS_TFBSET ; 
 scalar_t__ CS_TGRLD0 ; 
 scalar_t__ CS_WCRCEIL ; 
 scalar_t__ CS_WCRDEC ; 
 scalar_t__ CS_WCRINC ; 
 scalar_t__ CS_WCRMAX ; 
 scalar_t__ CS_WCRMIN ; 
 scalar_t__ he_is622 (struct he_dev*) ; 
 int /*<<< orphan*/  he_writel_mbox (struct he_dev*,int,scalar_t__) ; 

__attribute__((used)) static void he_init_cs_block(struct he_dev *he_dev)
{
	unsigned clock, rate, delta;
	int reg;

	/* 5.1.7 cs block initialization */

	for (reg = 0; reg < 0x20; ++reg)
		he_writel_mbox(he_dev, 0x0, CS_STTIM0 + reg);

	/* rate grid timer reload values */

	clock = he_is622(he_dev) ? 66667000 : 50000000;
	rate = he_dev->atm_dev->link_rate;
	delta = rate / 16 / 2;

	for (reg = 0; reg < 0x10; ++reg) {
		/* 2.4 internal transmit function
		 *
	 	 * we initialize the first row in the rate grid.
		 * values are period (in clock cycles) of timer
		 */
		unsigned period = clock / rate;

		he_writel_mbox(he_dev, period, CS_TGRLD0 + reg);
		rate -= delta;
	}

	if (he_is622(he_dev)) {
		/* table 5.2 (4 cells per lbuf) */
		he_writel_mbox(he_dev, 0x000800fa, CS_ERTHR0);
		he_writel_mbox(he_dev, 0x000c33cb, CS_ERTHR1);
		he_writel_mbox(he_dev, 0x0010101b, CS_ERTHR2);
		he_writel_mbox(he_dev, 0x00181dac, CS_ERTHR3);
		he_writel_mbox(he_dev, 0x00280600, CS_ERTHR4);

		/* table 5.3, 5.4, 5.5, 5.6, 5.7 */
		he_writel_mbox(he_dev, 0x023de8b3, CS_ERCTL0);
		he_writel_mbox(he_dev, 0x1801, CS_ERCTL1);
		he_writel_mbox(he_dev, 0x68b3, CS_ERCTL2);
		he_writel_mbox(he_dev, 0x1280, CS_ERSTAT0);
		he_writel_mbox(he_dev, 0x68b3, CS_ERSTAT1);
		he_writel_mbox(he_dev, 0x14585, CS_RTFWR);

		he_writel_mbox(he_dev, 0x4680, CS_RTATR);

		/* table 5.8 */
		he_writel_mbox(he_dev, 0x00159ece, CS_TFBSET);
		he_writel_mbox(he_dev, 0x68b3, CS_WCRMAX);
		he_writel_mbox(he_dev, 0x5eb3, CS_WCRMIN);
		he_writel_mbox(he_dev, 0xe8b3, CS_WCRINC);
		he_writel_mbox(he_dev, 0xdeb3, CS_WCRDEC);
		he_writel_mbox(he_dev, 0x68b3, CS_WCRCEIL);

		/* table 5.9 */
		he_writel_mbox(he_dev, 0x5, CS_OTPPER);
		he_writel_mbox(he_dev, 0x14, CS_OTWPER);
	} else {
		/* table 5.1 (4 cells per lbuf) */
		he_writel_mbox(he_dev, 0x000400ea, CS_ERTHR0);
		he_writel_mbox(he_dev, 0x00063388, CS_ERTHR1);
		he_writel_mbox(he_dev, 0x00081018, CS_ERTHR2);
		he_writel_mbox(he_dev, 0x000c1dac, CS_ERTHR3);
		he_writel_mbox(he_dev, 0x0014051a, CS_ERTHR4);

		/* table 5.3, 5.4, 5.5, 5.6, 5.7 */
		he_writel_mbox(he_dev, 0x0235e4b1, CS_ERCTL0);
		he_writel_mbox(he_dev, 0x4701, CS_ERCTL1);
		he_writel_mbox(he_dev, 0x64b1, CS_ERCTL2);
		he_writel_mbox(he_dev, 0x1280, CS_ERSTAT0);
		he_writel_mbox(he_dev, 0x64b1, CS_ERSTAT1);
		he_writel_mbox(he_dev, 0xf424, CS_RTFWR);

		he_writel_mbox(he_dev, 0x4680, CS_RTATR);

		/* table 5.8 */
		he_writel_mbox(he_dev, 0x000563b7, CS_TFBSET);
		he_writel_mbox(he_dev, 0x64b1, CS_WCRMAX);
		he_writel_mbox(he_dev, 0x5ab1, CS_WCRMIN);
		he_writel_mbox(he_dev, 0xe4b1, CS_WCRINC);
		he_writel_mbox(he_dev, 0xdab1, CS_WCRDEC);
		he_writel_mbox(he_dev, 0x64b1, CS_WCRCEIL);

		/* table 5.9 */
		he_writel_mbox(he_dev, 0x6, CS_OTPPER);
		he_writel_mbox(he_dev, 0x1e, CS_OTWPER);
	}

	he_writel_mbox(he_dev, 0x8, CS_OTTLIM);

	for (reg = 0; reg < 0x8; ++reg)
		he_writel_mbox(he_dev, 0x0, CS_HGRRT0 + reg);

}