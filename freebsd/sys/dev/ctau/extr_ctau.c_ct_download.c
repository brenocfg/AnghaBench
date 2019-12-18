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
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_3__ {long end; long start; } ;
typedef  TYPE_1__ cr_dat_tst_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (int /*<<< orphan*/ ) ; 
 unsigned char BCR0_TCK ; 
 int /*<<< orphan*/  BCR1 (int /*<<< orphan*/ ) ; 
 unsigned char BCR1_TDI ; 
 unsigned char BCR1_TMS ; 
 int /*<<< orphan*/  BSR2 (int /*<<< orphan*/ ) ; 
 unsigned char BSR2_LERR ; 
 int /*<<< orphan*/  BSR3 (int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

int ct_download (port_t port, const unsigned char *firmware,
	long bits, const cr_dat_tst_t *tst)
{
	unsigned char cr1, sr2;
	long i, n, maxn = (bits + 7) >> 3;
	int v, b;

	inb (BSR3(port));
	for (i=n=0; n<maxn; ++n) {
		v = ((firmware[n] ^ ' ') << 1) | ((firmware[n] >> 7) & 1);
		for (b=0; b<7; b+=2, i+=2) {
			if (i >= bits)
				break;
			cr1 = 0;
			if (v >> b & 1)
				cr1 |= BCR1_TMS;
			if (v >> b & 2)
				cr1 |= BCR1_TDI;
			outb (BCR1(port), cr1);
			sr2 = inb (BSR2(port));
			outb (BCR0(port), BCR0_TCK);
			outb (BCR0(port), 0);
			if (i >= tst->end)
				++tst;
			if (i >= tst->start && (sr2 & BSR2_LERR))
				return (0);
		}
	}
	return (1);
}