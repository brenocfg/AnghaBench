#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cfg; scalar_t__ clk1; scalar_t__ clk0; } ;
struct TYPE_9__ {int gmd0; int gmd1; int gmd2; int /*<<< orphan*/  port; TYPE_4__* chan; TYPE_2__ opt; } ;
typedef  TYPE_3__ ct_board_t ;
struct TYPE_7__ {int rate; scalar_t__ pce2; scalar_t__ pce; } ;
struct TYPE_10__ {int lx; TYPE_1__ gopt; } ;

/* Variables and functions */
 scalar_t__ CFG_B ; 
 int /*<<< orphan*/  GERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMD0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMD1 (int /*<<< orphan*/ ) ; 
 int GMD1_NCS0 ; 
 int GMD1_NCS1 ; 
 int /*<<< orphan*/  GMD2 (int /*<<< orphan*/ ) ; 
 int GMD2_LED ; 
 int GMD2_SERIAL ; 
 int GMD_1024 ; 
 int GMD_128 ; 
 int GMD_2048 ; 
 int GMD_256 ; 
 int GMD_512 ; 
 int GMD_64 ; 
 int GMD_PCE_PCM2 ; 
 int GMD_PCE_PCM2D ; 
 int GMD_RSYNC ; 
 int LX_LLOOP ; 
 int /*<<< orphan*/  ct_enable_loop (TYPE_4__*) ; 
 int /*<<< orphan*/  ct_setup_lxt (TYPE_4__*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void ct_setup_g703 (ct_board_t *b)
{
	b->gmd0 = GMD_2048;
	if (b->chan[0].gopt.pce) {
		if (b->chan[0].gopt.pce2) b->gmd0 |= GMD_PCE_PCM2;
		else			  b->gmd0 |= GMD_PCE_PCM2D;
	}
	if (b->opt.clk0)
		b->gmd0 |= GMD_RSYNC;

	b->gmd1 = 0;
	if (b->chan[1].gopt.pce) {
		if (b->chan[1].gopt.pce2) b->gmd1 |= GMD_PCE_PCM2;
		else			  b->gmd1 |= GMD_PCE_PCM2D;
	}
	if (b->opt.clk1)
		b->gmd1 |= GMD_RSYNC;

	switch (b->chan[0].gopt.rate) {
	case 2048: b->gmd0 |= GMD_2048; break;
	case 1024: b->gmd0 |= GMD_1024; break;
	case 512:  b->gmd0 |= GMD_512;	break;
	case 256:  b->gmd0 |= GMD_256;	break;
	case 128:  b->gmd0 |= GMD_128;	break;
	case 64:   b->gmd0 |= GMD_64;	break;
	}
	switch (b->chan[1].gopt.rate) {
	case 2048: b->gmd1 |= GMD_2048; break;
	case 1024: b->gmd1 |= GMD_1024; break;
	case 512:  b->gmd1 |= GMD_512;	break;
	case 256:  b->gmd1 |= GMD_256;	break;

	case 128:  b->gmd1 |= GMD_128;	break;
	case 64:   b->gmd1 |= GMD_64;	break;
	}

	outb (GMD0(b->port), b->gmd0);
	outb (GMD1(b->port), b->gmd1 | GMD1_NCS0 | GMD1_NCS1);

	b->gmd2 &= GMD2_LED;
	if (b->opt.cfg == CFG_B)   b->gmd2 |= GMD2_SERIAL;
	outb (GMD2(b->port), b->gmd2);

	/* Set up G.703 controllers. */
	if ((b->chan + 0)->lx & LX_LLOOP) {
		ct_setup_lxt (b->chan + 0);	/* channel 0 */
		ct_enable_loop (b->chan + 0);
	} else {
		ct_setup_lxt (b->chan + 0);	/* channel 0 */
	}
	if ((b->chan + 1)->lx & LX_LLOOP) {
		ct_setup_lxt (b->chan + 1);	/* channel 1 */
		ct_enable_loop (b->chan + 1);
	} else {
		ct_setup_lxt (b->chan + 1);	/* channel 1 */
	}

	/* Clear errors. */
	outb (GERR(b->port), 0xff);
	outb (GLDR(b->port), 0xff);
}