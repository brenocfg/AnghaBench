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
typedef  int vr41xx_clock_t ;

/* Variables and functions */
#define  AIU_CLOCK 140 
#define  CEU_CLOCK 139 
 int /*<<< orphan*/  CMUCLKMSK ; 
 int /*<<< orphan*/  CMUCLKMSK2 ; 
 int /*<<< orphan*/  CPU_VR4111 ; 
 int /*<<< orphan*/  CPU_VR4121 ; 
#define  CSI_CLOCK 138 
#define  DSIU_CLOCK 137 
#define  ETHER0_CLOCK 136 
#define  ETHER1_CLOCK 135 
#define  FIR_CLOCK 134 
#define  HSP_CLOCK 133 
#define  KIU_CLOCK 132 
 int MSKAIU ; 
 int MSKCEU ; 
 int MSKCSI ; 
 int MSKDSIU ; 
 int MSKFFIR ; 
 int MSKFIR ; 
 int MSKKIU ; 
 int MSKMAC0 ; 
 int MSKMAC1 ; 
 int MSKPCIU ; 
 int MSKPIU ; 
 int MSKPPCIU ; 
 int MSKSCSI ; 
 int MSKSHSP ; 
 int MSKSIU ; 
 int MSKSSIU ; 
#define  PCIU_CLOCK 131 
#define  PCI_CLOCK 130 
#define  PIU_CLOCK 129 
#define  SIU_CLOCK 128 
 int /*<<< orphan*/  cmu_lock ; 
 int /*<<< orphan*/  cmu_write (int /*<<< orphan*/ ,int) ; 
 int cmuclkmsk ; 
 int cmuclkmsk2 ; 
 int /*<<< orphan*/  current_cpu_type () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void vr41xx_mask_clock(vr41xx_clock_t clock)
{
	spin_lock_irq(&cmu_lock);

	switch (clock) {
	case PIU_CLOCK:
		cmuclkmsk &= ~MSKPIU;
		break;
	case SIU_CLOCK:
		if (current_cpu_type() == CPU_VR4111 ||
		    current_cpu_type() == CPU_VR4121) {
			cmuclkmsk &= ~(MSKSIU | MSKSSIU);
		} else {
			if (cmuclkmsk & MSKDSIU)
				cmuclkmsk &= ~MSKSSIU;
			else
				cmuclkmsk &= ~(MSKSIU | MSKSSIU);
		}
		break;
	case AIU_CLOCK:
		cmuclkmsk &= ~MSKAIU;
		break;
	case KIU_CLOCK:
		cmuclkmsk &= ~MSKKIU;
		break;
	case FIR_CLOCK:
		cmuclkmsk &= ~(MSKFIR | MSKFFIR);
		break;
	case DSIU_CLOCK:
		if (current_cpu_type() == CPU_VR4111 ||
		    current_cpu_type() == CPU_VR4121) {
			cmuclkmsk &= ~MSKDSIU;
		} else {
			if (cmuclkmsk & MSKSSIU)
				cmuclkmsk &= ~MSKDSIU;
			else
				cmuclkmsk &= ~(MSKSIU | MSKDSIU);
		}
		break;
	case CSI_CLOCK:
		cmuclkmsk &= ~(MSKCSI | MSKSCSI);
		break;
	case PCIU_CLOCK:
		cmuclkmsk &= ~MSKPCIU;
		break;
	case HSP_CLOCK:
		cmuclkmsk &= ~MSKSHSP;
		break;
	case PCI_CLOCK:
		cmuclkmsk &= ~MSKPPCIU;
		break;
	case CEU_CLOCK:
		cmuclkmsk2 &= ~MSKCEU;
		break;
	case ETHER0_CLOCK:
		cmuclkmsk2 &= ~MSKMAC0;
		break;
	case ETHER1_CLOCK:
		cmuclkmsk2 &= ~MSKMAC1;
		break;
	default:
		break;
	}

	if (clock == CEU_CLOCK || clock == ETHER0_CLOCK ||
	    clock == ETHER1_CLOCK)
		cmu_write(CMUCLKMSK2, cmuclkmsk2);
	else
		cmu_write(CMUCLKMSK, cmuclkmsk);

	spin_unlock_irq(&cmu_lock);
}