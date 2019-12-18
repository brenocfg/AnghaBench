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
typedef  int /*<<< orphan*/  ct_chan_t ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/ * chan; int /*<<< orphan*/  port; int /*<<< orphan*/  bcr1; } ;
typedef  TYPE_1__ ct_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSR0 (int /*<<< orphan*/ ) ; 
 unsigned char BSR0_GINT ; 
 unsigned char BSR0_HDINT ; 
 unsigned char BSR0_INTR ; 
 unsigned char BSR0_RDYERR ; 
 scalar_t__ B_TAU2_E1 ; 
 scalar_t__ B_TAU2_E1D ; 
 scalar_t__ B_TAU_E1 ; 
 scalar_t__ B_TAU_E1C ; 
 scalar_t__ B_TAU_E1D ; 
 int /*<<< orphan*/  IACK (int /*<<< orphan*/ ) ; 
 unsigned char IMVR_CHAN1 ; 
 int /*<<< orphan*/  ct_e1_interrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  ct_hdlc_interrupt (int /*<<< orphan*/ *,unsigned char) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ct_int_handler (ct_board_t *b)
{
	unsigned char bsr0, imvr;
	ct_chan_t *c;

	while ((bsr0 = inb (BSR0(b->port))) & BSR0_INTR) {
		if (bsr0 & BSR0_RDYERR) {
			outb (BCR1(b->port), b->bcr1);
		} else if (bsr0 & BSR0_GINT) {
			if (b->type == B_TAU_E1 || b->type == B_TAU_E1C ||
			    b->type == B_TAU_E1D || b->type == B_TAU2_E1 ||
			    b->type == B_TAU2_E1D)
				ct_e1_interrupt (b);
		} else if (bsr0 & BSR0_HDINT) {
			/* Read the interrupt modified vector register. */
			imvr = inb (IACK(b->port));
			c = b->chan + (imvr & IMVR_CHAN1 ? 1 : 0);
			ct_hdlc_interrupt (c, imvr);
		}
	}
}