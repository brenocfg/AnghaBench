#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ port_t ;
struct TYPE_5__ {long oscfreq; int num; int type; TYPE_2__* board; void* port; } ;
typedef  TYPE_1__ cx_chan_t ;
struct TYPE_6__ {int num; int irq; int dma; int bcr0; int bcr0b; scalar_t__ nsync; scalar_t__ nuniv; scalar_t__ nasync; TYPE_1__* chan; int /*<<< orphan*/  name; scalar_t__ bcr1b; scalar_t__ bcr1; int /*<<< orphan*/  if8type; int /*<<< orphan*/  if0type; int /*<<< orphan*/  type; int /*<<< orphan*/  opt; scalar_t__ port; } ;
typedef  TYPE_2__ cx_board_t ;

/* Variables and functions */
 int BCR0_NORESET ; 
#define  BSR_OSC_18432 152 
#define  BSR_OSC_20 151 
 int /*<<< orphan*/  B_SIGMA_XXX ; 
#define  CRONYX_100 150 
#define  CRONYX_400 149 
#define  CRONYX_401 148 
#define  CRONYX_401s 147 
#define  CRONYX_404 146 
#define  CRONYX_410 145 
#define  CRONYX_410s 144 
#define  CRONYX_440 143 
#define  CRONYX_500 142 
#define  CRONYX_703 141 
#define  CRONYX_801 140 
#define  CRONYX_801s 139 
#define  CRONYX_810 138 
#define  CRONYX_810s 137 
#define  CRONYX_840 136 
 void* CS0 (scalar_t__) ; 
 void* CS1 (scalar_t__) ; 
 void* CS1A (scalar_t__) ; 
 int NCHAN ; 
#define  T_ASYNC 135 
 int T_NONE ; 
#define  T_SYNC_RS232 134 
#define  T_SYNC_RS449 133 
#define  T_SYNC_V35 132 
#define  T_UNIV 131 
#define  T_UNIV_RS232 130 
#define  T_UNIV_RS449 129 
#define  T_UNIV_V35 128 
 int /*<<< orphan*/  board_opt_dflt ; 
 int /*<<< orphan*/  cx_iftype ; 
 scalar_t__ cx_probe_chip (void*) ; 
 int /*<<< orphan*/  cx_reinit_board (TYPE_2__*) ; 
 int* dmamask ; 
 int* irqmask ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void cx_init_board (cx_board_t *b, int num, port_t port, int irq, int dma,
	int chain, int rev, int osc, int mod, int rev2, int osc2, int mod2)
{
	cx_chan_t *c;
	char *type;
	int i;

	/* Initialize board structure. */
	b->port = port;
	b->num = num;
	b->irq = irq;
	b->dma = dma;
	b->opt = board_opt_dflt;

	b->type = B_SIGMA_XXX;
	b->if0type = b->if8type = cx_iftype;

	/* Set channels 0 and 8 mode, set DMA and IRQ. */
	b->bcr0 = b->bcr0b = BCR0_NORESET | dmamask[b->dma] | irqmask[b->irq];

	/* Clear DTR[0..3] and DTR[8..12]. */
	b->bcr1 = b->bcr1b = 0;

	/*------------------ Master board -------------------*/

	/* Read and check the board revision code. */
	strcpy (b->name, mod ? "m" : "");
	switch (rev) {
	default:	  type = "";	 break;
	case CRONYX_100:  type = "100";  break;
	case CRONYX_400:  type = "400";  break;
	case CRONYX_500:  type = "500";  break;
	case CRONYX_410:  type = "410";  break;
	case CRONYX_810:  type = "810";  break;
	case CRONYX_410s: type = "410s"; break;
	case CRONYX_810s: type = "810s"; break;
	case CRONYX_440:  type = "440";  break;
	case CRONYX_840:  type = "840";  break;
	case CRONYX_401:  type = "401";  break;
	case CRONYX_801:  type = "801";  break;
	case CRONYX_401s: type = "401s"; break;
	case CRONYX_801s: type = "801s"; break;
	case CRONYX_404:  type = "404";  break;
	case CRONYX_703:  type = "703";  break;
	}
	strcat (b->name, type);

	switch (osc) {
	default:
	case BSR_OSC_20: /* 20 MHz */
		b->chan[0].oscfreq = b->chan[1].oscfreq =
		b->chan[2].oscfreq = b->chan[3].oscfreq =
		b->chan[4].oscfreq = b->chan[5].oscfreq =
		b->chan[6].oscfreq = b->chan[7].oscfreq =
			mod ? 33000000L : 20000000L;
		strcat (b->name, "a");
		break;
	case BSR_OSC_18432: /* 18.432 MHz */
		b->chan[0].oscfreq = b->chan[1].oscfreq =
		b->chan[2].oscfreq = b->chan[3].oscfreq =
		b->chan[4].oscfreq = b->chan[5].oscfreq =
		b->chan[6].oscfreq = b->chan[7].oscfreq =
			mod ? 20000000L : 18432000L;
		strcat (b->name, "b");
		break;
	}

	/*------------------ Slave board -------------------*/

	if (chain) {
		/* Read and check the board revision code. */
		strcat (b->name, mod2 ? "/m" : "/");
		switch (rev2) {
		default:	  type = "";	 break;
		case CRONYX_100:  type = "100";  break;
		case CRONYX_400:  type = "400";  break;
		case CRONYX_500:  type = "500";  break;
		case CRONYX_410:  type = "410";  break;
		case CRONYX_810:  type = "810";  break;
		case CRONYX_410s: type = "410s"; break;
		case CRONYX_810s: type = "810s"; break;
		case CRONYX_440:  type = "440";  break;
		case CRONYX_840:  type = "840";  break;
		case CRONYX_401:  type = "401";  break;
		case CRONYX_801:  type = "801";  break;
		case CRONYX_401s: type = "401s"; break;
		case CRONYX_801s: type = "801s"; break;
		case CRONYX_404:  type = "404";  break;
		case CRONYX_703:  type = "703";  break;
		}
		strcat (b->name, type);

		switch (osc2) {
		default:
		case BSR_OSC_20: /* 20 MHz */
			b->chan[8].oscfreq = b->chan[9].oscfreq =
			b->chan[10].oscfreq = b->chan[11].oscfreq =
			b->chan[12].oscfreq = b->chan[13].oscfreq =
			b->chan[14].oscfreq = b->chan[15].oscfreq =
				mod2 ? 33000000L : 20000000L;
			strcat (b->name, "a");
			break;
		case BSR_OSC_18432: /* 18.432 MHz */
			b->chan[8].oscfreq = b->chan[9].oscfreq =
			b->chan[10].oscfreq = b->chan[11].oscfreq =
			b->chan[12].oscfreq = b->chan[13].oscfreq =
			b->chan[14].oscfreq = b->chan[15].oscfreq =
				mod2 ? 20000000L : 18432000L;
			strcat (b->name, "b");
			break;
		}
	}

	/* Initialize channel structures. */
	for (i=0; i<4; ++i) {
		b->chan[i+0].port  = CS0(port);
		b->chan[i+4].port  = cx_probe_chip (CS1A(port)) ?
			CS1A(port) : CS1(port);
		b->chan[i+8].port  = CS0(port+0x10);
		b->chan[i+12].port = CS1(port+0x10);
	}
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		c->board = b;
		c->num = c - b->chan;
		c->type = T_NONE;
	}

	/*------------------ Master board -------------------*/

	switch (rev) {
	case CRONYX_400:
		for (i=4; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_100:
		b->chan[0].type = T_UNIV_RS232;
		break;
	case CRONYX_500:
		b->chan[0].type = T_UNIV_RS232;
		for (i=4; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_410:
		b->chan[0].type = T_UNIV_V35;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_810:
		b->chan[0].type = T_UNIV_V35;
		for (i=1; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_410s:
		b->chan[0].type = T_UNIV_V35;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_RS232;
		break;
	case CRONYX_810s:
		b->chan[0].type = T_UNIV_V35;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_RS232;
		for (i=4; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_440:
		b->chan[0].type = T_UNIV_V35;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_V35;
		break;
	case CRONYX_840:
		b->chan[0].type = T_UNIV_V35;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_V35;
		for (i=4; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_401:
		b->chan[0].type = T_UNIV_RS449;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_801:
		b->chan[0].type = T_UNIV_RS449;
		for (i=1; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_401s:
		b->chan[0].type = T_UNIV_RS449;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_RS232;
		break;
	case CRONYX_801s:
		b->chan[0].type = T_UNIV_RS449;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_RS232;
		for (i=4; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	case CRONYX_404:
		b->chan[0].type = T_UNIV_RS449;
		for (i=1; i<4; ++i)
			b->chan[i].type = T_SYNC_RS449;
		break;
	case CRONYX_703:
		b->chan[0].type = T_UNIV_RS449;
		for (i=1; i<3; ++i)
			b->chan[i].type = T_SYNC_RS449;
		for (i=4; i<8; ++i)
			b->chan[i].type = T_UNIV_RS232;
		break;
	}

	/*------------------ Slave board -------------------*/

	if (chain) {
		switch (rev2) {
		case CRONYX_400:
			break;
		case CRONYX_100:
			b->chan[8].type = T_UNIV_RS232;
			break;
		case CRONYX_500:
			b->chan[8].type = T_UNIV_RS232;
			for (i=12; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_410:
			b->chan[8].type = T_UNIV_V35;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_810:
			b->chan[8].type = T_UNIV_V35;
			for (i=9; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_410s:
			b->chan[8].type = T_UNIV_V35;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_SYNC_RS232;
			break;
		case CRONYX_810s:
			b->chan[8].type = T_UNIV_V35;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_SYNC_RS232;
			for (i=12; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_440:
			b->chan[8].type = T_UNIV_V35;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_SYNC_V35;
			break;
		case CRONYX_840:
			b->chan[8].type = T_UNIV_V35;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_SYNC_V35;
			for (i=12; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_401:
			b->chan[8].type = T_UNIV_RS449;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_801:
			b->chan[8].type = T_UNIV_RS449;
			for (i=9; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_401s:
			b->chan[8].type = T_UNIV_RS449;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_801s:
			b->chan[8].type = T_UNIV_RS449;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_SYNC_RS232;
			for (i=12; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		case CRONYX_404:
			b->chan[8].type = T_UNIV_RS449;
			for (i=9; i<12; ++i)
				b->chan[i].type = T_SYNC_RS449;
			break;
		case CRONYX_703:
			b->chan[8].type = T_UNIV_RS449;
			for (i=9; i<11; ++i)
				b->chan[i].type = T_SYNC_RS449;
			for (i=12; i<16; ++i)
				b->chan[i].type = T_UNIV_RS232;
			break;
		}
	}

	b->nuniv = b->nsync = b->nasync = 0;
	for (c=b->chan; c<b->chan+NCHAN; ++c)
		switch (c->type) {
		case T_ASYNC:      ++b->nasync; break;
		case T_UNIV:
		case T_UNIV_RS232:
		case T_UNIV_RS449:
		case T_UNIV_V35:   ++b->nuniv;  break;
		case T_SYNC_RS232:
		case T_SYNC_V35:
		case T_SYNC_RS449: ++b->nsync;  break;
		}

	cx_reinit_board (b);
}