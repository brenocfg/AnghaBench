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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct musbotg_softc {TYPE_1__* sc_hw_ep_profile; } ;
struct TYPE_2__ {int max_in_frame_size; int max_out_frame_size; } ;

/* Variables and functions */
 int MUSB2_MASK_CSRH_RXISO ; 
 int MUSB2_MASK_CSRH_RXNYET ; 
 int MUSB2_MASK_CSRH_TXISO ; 
 int MUSB2_MASK_CSRH_TXMODE ; 
 int MUSB2_MASK_CSRL_RXDT_CLR ; 
 int MUSB2_MASK_CSRL_RXFFLUSH ; 
 scalar_t__ MUSB2_MASK_CSRL_RXPKTRDY ; 
 scalar_t__ MUSB2_MASK_CSRL_RXSENTSTALL ; 
 int MUSB2_MASK_CSRL_TXDT_CLR ; 
 int MUSB2_MASK_CSRL_TXFFLUSH ; 
 scalar_t__ MUSB2_MASK_CSRL_TXFIFONEMPTY ; 
 scalar_t__ MUSB2_MASK_CSRL_TXSENTSTALL ; 
 scalar_t__ MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int MUSB2_READ_2 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_RXCSRH ; 
 int /*<<< orphan*/  MUSB2_REG_RXCSRL ; 
 int /*<<< orphan*/  MUSB2_REG_RXDBDIS ; 
 int /*<<< orphan*/  MUSB2_REG_RXMAXP ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRH ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRL ; 
 int /*<<< orphan*/  MUSB2_REG_TXDBDIS ; 
 int /*<<< orphan*/  MUSB2_REG_TXMAXP ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MUSB2_WRITE_2 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
#define  UE_BULK 130 
 scalar_t__ UE_CONTROL ; 
 scalar_t__ UE_DIR_IN ; 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 

__attribute__((used)) static void
musbotg_clear_stall_sub(struct musbotg_softc *sc, uint16_t wMaxPacket,
    uint8_t ep_no, uint8_t ep_type, uint8_t ep_dir)
{
	uint16_t mps;
	uint16_t temp;
	uint8_t csr;

	if (ep_type == UE_CONTROL) {
		/* clearing stall is not needed */
		return;
	}
	/* select endpoint */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, ep_no);

	/* compute max frame size */
	mps = wMaxPacket & 0x7FF;
	switch ((wMaxPacket >> 11) & 3) {
	case 1:
		mps *= 2;
		break;
	case 2:
		mps *= 3;
		break;
	default:
		break;
	}

	if (ep_dir == UE_DIR_IN) {

		temp = 0;

		/* Configure endpoint */
		switch (ep_type) {
		case UE_INTERRUPT:
			MUSB2_WRITE_2(sc, MUSB2_REG_TXMAXP, wMaxPacket);
			MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRH,
			    MUSB2_MASK_CSRH_TXMODE | temp);
			break;
		case UE_ISOCHRONOUS:
			MUSB2_WRITE_2(sc, MUSB2_REG_TXMAXP, wMaxPacket);
			MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRH,
			    MUSB2_MASK_CSRH_TXMODE |
			    MUSB2_MASK_CSRH_TXISO | temp);
			break;
		case UE_BULK:
			MUSB2_WRITE_2(sc, MUSB2_REG_TXMAXP, wMaxPacket);
			MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRH,
			    MUSB2_MASK_CSRH_TXMODE | temp);
			break;
		default:
			break;
		}

		/* Need to flush twice in case of double bufring */
		csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
		if (csr & MUSB2_MASK_CSRL_TXFIFONEMPTY) {
			MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
			    MUSB2_MASK_CSRL_TXFFLUSH);
			csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
			if (csr & MUSB2_MASK_CSRL_TXFIFONEMPTY) {
				MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
				    MUSB2_MASK_CSRL_TXFFLUSH);
				csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
			}
		}
		/* reset data toggle */
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		    MUSB2_MASK_CSRL_TXDT_CLR);
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, 0);
		csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);

		/* set double/single buffering */
		temp = MUSB2_READ_2(sc, MUSB2_REG_TXDBDIS);
		if (mps <= (sc->sc_hw_ep_profile[ep_no].
		    max_in_frame_size / 2)) {
			/* double buffer */
			temp &= ~(1 << ep_no);
		} else {
			/* single buffer */
			temp |= (1 << ep_no);
		}
		MUSB2_WRITE_2(sc, MUSB2_REG_TXDBDIS, temp);

		/* clear sent stall */
		if (csr & MUSB2_MASK_CSRL_TXSENTSTALL) {
			MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL, 0);
			csr = MUSB2_READ_1(sc, MUSB2_REG_TXCSRL);
		}
	} else {

		temp = 0;

		/* Configure endpoint */
		switch (ep_type) {
		case UE_INTERRUPT:
			MUSB2_WRITE_2(sc, MUSB2_REG_RXMAXP, wMaxPacket);
			MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRH,
			    MUSB2_MASK_CSRH_RXNYET | temp);
			break;
		case UE_ISOCHRONOUS:
			MUSB2_WRITE_2(sc, MUSB2_REG_RXMAXP, wMaxPacket);
			MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRH,
			    MUSB2_MASK_CSRH_RXNYET |
			    MUSB2_MASK_CSRH_RXISO | temp);
			break;
		case UE_BULK:
			MUSB2_WRITE_2(sc, MUSB2_REG_RXMAXP, wMaxPacket);
			MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRH, temp);
			break;
		default:
			break;
		}

		/* Need to flush twice in case of double bufring */
		csr = MUSB2_READ_1(sc, MUSB2_REG_RXCSRL);
		if (csr & MUSB2_MASK_CSRL_RXPKTRDY) {
			MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL,
			    MUSB2_MASK_CSRL_RXFFLUSH);
			csr = MUSB2_READ_1(sc, MUSB2_REG_RXCSRL);
			if (csr & MUSB2_MASK_CSRL_RXPKTRDY) {
				MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL,
				    MUSB2_MASK_CSRL_RXFFLUSH);
				csr = MUSB2_READ_1(sc, MUSB2_REG_RXCSRL);
			}
		}
		/* reset data toggle */
		MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL,
		    MUSB2_MASK_CSRL_RXDT_CLR);
		MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL, 0);
		csr = MUSB2_READ_1(sc, MUSB2_REG_RXCSRL);

		/* set double/single buffering */
		temp = MUSB2_READ_2(sc, MUSB2_REG_RXDBDIS);
		if (mps <= (sc->sc_hw_ep_profile[ep_no].
		    max_out_frame_size / 2)) {
			/* double buffer */
			temp &= ~(1 << ep_no);
		} else {
			/* single buffer */
			temp |= (1 << ep_no);
		}
		MUSB2_WRITE_2(sc, MUSB2_REG_RXDBDIS, temp);

		/* clear sent stall */
		if (csr & MUSB2_MASK_CSRL_RXSENTSTALL) {
			MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL, 0);
		}
	}
}