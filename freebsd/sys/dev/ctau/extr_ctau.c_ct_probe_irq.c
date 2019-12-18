#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bcr0; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ ct_board_t ;

/* Variables and functions */
 int BCR0 (int /*<<< orphan*/ ) ; 
 int BCR0_HDRUN ; 
 int /*<<< orphan*/  DS_IMR2 ; 
 int /*<<< orphan*/  E1CS0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1CS1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HD_TCNT_0R ; 
 int /*<<< orphan*/  HD_TCONR_0R ; 
 int /*<<< orphan*/  HD_TCSR_0R ; 
 int /*<<< orphan*/  HD_TEPR_0R ; 
 int IER0 (int /*<<< orphan*/ ) ; 
 int IER1 (int /*<<< orphan*/ ) ; 
 int IER2 (int /*<<< orphan*/ ) ; 
 int IER2_RX_TME_0 ; 
 int R (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SR2_SEC ; 
 int TCSR_ENABLE ; 
 int TCSR_INTR ; 
 int /*<<< orphan*/  cte_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (int) ; 
 int* irqmask ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outw (int,int) ; 

int ct_probe_irq (ct_board_t *b, int irq)
{
	int mask;

	outb (0x20, 0x0a);
	mask = inb (0x20);
	outb (0xa0, 0x0a);
	mask |= inb (0xa0) << 8;

	if (irq > 0) {
		outb (BCR0(b->port), BCR0_HDRUN | irqmask[irq]);
		outb (R(b->port,HD_TEPR_0R), 0);
		outw (R(b->port,HD_TCONR_0R), 1);
		outw (R(b->port,HD_TCNT_0R), 0);
		outb (R(b->port,HD_TCSR_0R), TCSR_ENABLE | TCSR_INTR);
		outb (IER2(b->port), IER2_RX_TME_0);
	} else if (irq < 0) {
		outb (BCR0(b->port), BCR0_HDRUN | irqmask[-irq]);
		outb (IER0(b->port), 0);
		outb (IER1(b->port), 0);
		outb (IER2(b->port), 0);
		outb (R(b->port,HD_TCSR_0R), 0);
		cte_out (E1CS0 (b->port), DS_IMR2, 0);
		cte_out (E1CS1 (b->port), DS_IMR2, 0);
		if (-irq > 7) {
			outb (0xa0, 0x60 | ((-irq) & 7));
			outb (0x20, 0x62);
		} else
			outb (0x20, 0x60 | (-irq));
	} else {
		outb (BCR0(b->port), b->bcr0);
		cte_out (E1CS0 (b->port), DS_IMR2, SR2_SEC);
		cte_out (E1CS1 (b->port), DS_IMR2, SR2_SEC);
	}

	return mask;
}