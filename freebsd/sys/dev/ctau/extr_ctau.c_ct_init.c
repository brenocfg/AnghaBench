#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  port_t ;
typedef  int /*<<< orphan*/  ct_board_t ;
struct TYPE_4__ {int member_0; int member_1; } ;
typedef  TYPE_1__ const cr_dat_tst_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSR0 (int /*<<< orphan*/ ) ; 
 unsigned char BSR0_T703 ; 
 unsigned char BSR0_TE1 ; 
 int /*<<< orphan*/  BSR3 (int /*<<< orphan*/ ) ; 
 int BSR3_ZERO ; 
 int B_TAU ; 
 int B_TAU2 ; 
 int B_TAU2_E1 ; 
 int B_TAU2_E1D ; 
 int B_TAU2_G703 ; 
 int B_TAU_E1 ; 
 int B_TAU_E1C ; 
 int B_TAU_E1D ; 
 int B_TAU_G703 ; 
 int B_TAU_G703C ; 
 int /*<<< orphan*/  E1SR (int /*<<< orphan*/ ) ; 
 int E1SR_REV ; 
 scalar_t__ ct_download (int /*<<< orphan*/ ,unsigned char const*,long,TYPE_1__ const*) ; 
 scalar_t__ ct_download2 (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  ct_init_board (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int,long) ; 
 scalar_t__ ct_probe2_board (int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 

void ct_init (ct_board_t *b, int num, port_t port, int irq, int dma,
	const unsigned char *firmware, long bits, const cr_dat_tst_t *tst,
	const unsigned char *firmware2)
{
	static long tlen	       = 182;
	static cr_dat_tst_t tvec []    = {{ 114, 178 }, { 182, 182 }};
	static cr_dat_tst_t tvec2 []   = {{ 50,  178 }, { 182, 182 }};
	static unsigned char tau []    = { 155,153,113,48,64,236,
		48,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,183,};
	static unsigned char e1 []     = { 155,153,113,48,64,236,
		112,37,49,37,33,116,101,100,112,37,49,37,33,116,101,100,230,};
	static unsigned char e1_2 []   = { 155,153,113,48,64,236,
		112,37,49,37,33,116,101,100,96,97,53,49,49,96,97,100,230,};
	static unsigned char e1_3 []   = { 155,153,113,48,64,236,
		96,97,53,49,49,96,97,100,96,97,53,49,49,96,97,100,230,};
	static unsigned char e1_4 []   = { 155,153,113,48,64,236,
		96,97,53,49,49,96,97,100,112,37,49,37,33,116,101,100,230,};
	static unsigned char g703 []   = { 155,153,113,48,64,236,
		112,37,49,37,33,116,101,32,117,37,49,37,33,116,101,100,230,};
	static unsigned char g703_2 [] = { 155,153,113,48,64,236,
		112,37,49,37,33,116,101,32,101,97,53,49,49,96,97,100,230,};
	static unsigned char g703_3 [] = { 155,153,113,48,64,236,
		96,97,53,49,49,96,97,32,101,97,53,49,49,96,97,100,230,};
	static unsigned char g703_4 [] = { 155,153,113,48,64,236,
		96,97,53,49,49,96,97,32,117,37,49,37,33,116,101,100,230,};

	int type = B_TAU;
	long osc = (inb (BSR3(port)) & BSR3_ZERO) ? 8192000 : 10000000;

	/* Get the board type. */
	if (ct_probe2_board (port) && ct_download2 (port, firmware2)) {
		/* Tau2, 1k30-based model */
		unsigned char sr0 = inb (BSR0(port));
		if (! (sr0 & BSR0_T703))
			type = B_TAU2_G703;
		else if (sr0 & BSR0_TE1)
			type = B_TAU2;
		else if (inb(E1SR(port)) & E1SR_REV)
			type = B_TAU2_E1D;
		else
			type = B_TAU2_E1;
	} else if (ct_download (port, tau, tlen, tvec)) {
		if (! ct_download (port, firmware, bits, tst))
			type = B_TAU;
		else {
			unsigned char sr0 = inb (BSR0(port));
			if (! (sr0 & BSR0_T703))
				type = B_TAU_G703C;
			else if (sr0 & BSR0_TE1)
				type = B_TAU;
			else if (inb(E1SR(port)) & E1SR_REV)
				type = B_TAU_E1D;
			else
				type = B_TAU_E1C;
		}
	} else if (ct_download (port, e1, tlen, tvec2) ||
	    ct_download (port, e1_2, tlen, tvec2) ||
	    ct_download (port, e1_3, tlen, tvec2) ||
	    ct_download (port, e1_4, tlen, tvec2))
		type = B_TAU_E1;
	else if (ct_download (port, g703, tlen, tvec2) ||
	    ct_download (port, g703_2, tlen, tvec2) ||
	    ct_download (port, g703_3, tlen, tvec2) ||
	    ct_download (port, g703_4, tlen, tvec2))
		type = B_TAU_G703;
	ct_init_board (b, num, port, irq, dma, type, osc);
}