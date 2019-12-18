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
typedef  int uint32_t ;
struct bcm_intc_softc {int dummy; } ;

/* Variables and functions */
 int BANK1_START ; 
 int BANK2_START ; 
 int /*<<< orphan*/  INTC_PENDING_BANK1 ; 
 int INTC_PENDING_BANK1_MASK ; 
 int /*<<< orphan*/  INTC_PENDING_BANK2 ; 
 int INTC_PENDING_BANK2_MASK ; 
 int /*<<< orphan*/  INTC_PENDING_BASIC ; 
 int INTC_PENDING_BASIC_ARM ; 
 int INTC_PENDING_BASIC_GPU1_10 ; 
 int INTC_PENDING_BASIC_GPU1_18 ; 
 int INTC_PENDING_BASIC_GPU1_19 ; 
 int INTC_PENDING_BASIC_GPU1_7 ; 
 int INTC_PENDING_BASIC_GPU1_9 ; 
 int INTC_PENDING_BASIC_GPU1_MASK ; 
 int INTC_PENDING_BASIC_GPU1_PEND ; 
 int INTC_PENDING_BASIC_GPU2_21 ; 
 int INTC_PENDING_BASIC_GPU2_22 ; 
 int INTC_PENDING_BASIC_GPU2_23 ; 
 int INTC_PENDING_BASIC_GPU2_24 ; 
 int INTC_PENDING_BASIC_GPU2_25 ; 
 int INTC_PENDING_BASIC_GPU2_30 ; 
 int INTC_PENDING_BASIC_GPU2_MASK ; 
 int INTC_PENDING_BASIC_GPU2_PEND ; 
 int INTC_PENDING_BASIC_MASK ; 
 int ffs (int) ; 
 int intc_read_4 (struct bcm_intc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bcm2835_intc_active_intr(struct bcm_intc_softc *sc)
{
	uint32_t pending, pending_gpu;

	pending = intc_read_4(sc, INTC_PENDING_BASIC) & INTC_PENDING_BASIC_MASK;
	if (pending == 0)
		return (-1);
	if (pending & INTC_PENDING_BASIC_ARM)
		return (ffs(pending) - 1);
	if (pending & INTC_PENDING_BASIC_GPU1_MASK) {
		if (pending & INTC_PENDING_BASIC_GPU1_7)
			return (BANK1_START + 7);
		if (pending & INTC_PENDING_BASIC_GPU1_9)
			return (BANK1_START + 9);
		if (pending & INTC_PENDING_BASIC_GPU1_10)
			return (BANK1_START + 10);
		if (pending & INTC_PENDING_BASIC_GPU1_18)
			return (BANK1_START + 18);
		if (pending & INTC_PENDING_BASIC_GPU1_19)
			return (BANK1_START + 19);
	}
	if (pending & INTC_PENDING_BASIC_GPU2_MASK) {
		if (pending & INTC_PENDING_BASIC_GPU2_21)
			return (BANK2_START + 21);
		if (pending & INTC_PENDING_BASIC_GPU2_22)
			return (BANK2_START + 22);
		if (pending & INTC_PENDING_BASIC_GPU2_23)
			return (BANK2_START + 23);
		if (pending & INTC_PENDING_BASIC_GPU2_24)
			return (BANK2_START + 24);
		if (pending & INTC_PENDING_BASIC_GPU2_25)
			return (BANK2_START + 25);
		if (pending & INTC_PENDING_BASIC_GPU2_30)
			return (BANK2_START + 30);
	}
	if (pending & INTC_PENDING_BASIC_GPU1_PEND) {
		pending_gpu = intc_read_4(sc, INTC_PENDING_BANK1);
		pending_gpu &= INTC_PENDING_BANK1_MASK;
		if (pending_gpu != 0)
			return (BANK1_START + ffs(pending_gpu) - 1);
	}
	if (pending & INTC_PENDING_BASIC_GPU2_PEND) {
		pending_gpu = intc_read_4(sc, INTC_PENDING_BANK2);
		pending_gpu &= INTC_PENDING_BANK2_MASK;
		if (pending_gpu != 0)
			return (BANK2_START + ffs(pending_gpu) - 1);
	}
	return (-1);	/* It shouldn't end here, but it's hardware. */
}