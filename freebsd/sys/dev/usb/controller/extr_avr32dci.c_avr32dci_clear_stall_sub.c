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
typedef  int uint32_t ;
struct usb_hw_ep_profile {int max_in_frame_size; int max_out_frame_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct avr32dci_softc {TYPE_1__ sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_EPTCFG (scalar_t__) ; 
 int AVR32_EPTCFG_EPDIR_IN ; 
 int AVR32_EPTCFG_EPSIZE (scalar_t__) ; 
 int AVR32_EPTCFG_EPT_MAPD ; 
 int AVR32_EPTCFG_NBANK (int) ; 
 int AVR32_EPTCFG_NB_TRANS (int) ; 
 int AVR32_EPTCFG_TYPE_BULK ; 
 int AVR32_EPTCFG_TYPE_INTR ; 
 int AVR32_EPTCFG_TYPE_ISOC ; 
 int /*<<< orphan*/  AVR32_EPTCLRSTA (scalar_t__) ; 
 int /*<<< orphan*/  AVR32_EPTCTLENB (scalar_t__) ; 
 int AVR32_EPTCTL_EPT_ENABL ; 
 int /*<<< orphan*/  AVR32_EPTRST ; 
 int AVR32_EPTRST_MASK (scalar_t__) ; 
 int /*<<< orphan*/  AVR32_EPTSETSTA (scalar_t__) ; 
 int AVR32_EPTSTA_FRCESTALL ; 
 int AVR32_EPTSTA_TOGGLESQ ; 
 int AVR32_READ_4 (struct avr32dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ UE_BULK ; 
 scalar_t__ UE_CONTROL ; 
 scalar_t__ UE_DIR_IN ; 
 scalar_t__ UE_INTERRUPT ; 
 int /*<<< orphan*/  avr32dci_get_hw_ep_profile (int /*<<< orphan*/ *,struct usb_hw_ep_profile const**,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
avr32dci_clear_stall_sub(struct avr32dci_softc *sc, uint8_t ep_no,
    uint8_t ep_type, uint8_t ep_dir)
{
	const struct usb_hw_ep_profile *pf;
	uint32_t temp;
	uint32_t epsize;
	uint8_t n;

	if (ep_type == UE_CONTROL) {
		/* clearing stall is not needed */
		return;
	}
	/* set endpoint reset */
	AVR32_WRITE_4(sc, AVR32_EPTRST, AVR32_EPTRST_MASK(ep_no));

	/* set stall */
	AVR32_WRITE_4(sc, AVR32_EPTSETSTA(ep_no), AVR32_EPTSTA_FRCESTALL);

	/* reset data toggle */
	AVR32_WRITE_4(sc, AVR32_EPTCLRSTA(ep_no), AVR32_EPTSTA_TOGGLESQ);

	/* clear stall */
	AVR32_WRITE_4(sc, AVR32_EPTCLRSTA(ep_no), AVR32_EPTSTA_FRCESTALL);

	if (ep_type == UE_BULK) {
		temp = AVR32_EPTCFG_TYPE_BULK;
	} else if (ep_type == UE_INTERRUPT) {
		temp = AVR32_EPTCFG_TYPE_INTR;
	} else {
		temp = AVR32_EPTCFG_TYPE_ISOC |
		    AVR32_EPTCFG_NB_TRANS(1);
	}
	if (ep_dir & UE_DIR_IN) {
		temp |= AVR32_EPTCFG_EPDIR_IN;
	}
	avr32dci_get_hw_ep_profile(NULL, &pf, ep_no);

	/* compute endpoint size (use maximum) */
	epsize = pf->max_in_frame_size | pf->max_out_frame_size;
	n = 0;
	while ((epsize /= 2))
		n++;
	temp |= AVR32_EPTCFG_EPSIZE(n);

	/* use the maximum number of banks supported */
	if (ep_no < 1)
		temp |= AVR32_EPTCFG_NBANK(1);
	else if (ep_no < 3)
		temp |= AVR32_EPTCFG_NBANK(2);
	else
		temp |= AVR32_EPTCFG_NBANK(3);

	AVR32_WRITE_4(sc, AVR32_EPTCFG(ep_no), temp);

	temp = AVR32_READ_4(sc, AVR32_EPTCFG(ep_no));

	if (!(temp & AVR32_EPTCFG_EPT_MAPD)) {
		device_printf(sc->sc_bus.bdev, "Chip rejected configuration\n");
	} else {
		AVR32_WRITE_4(sc, AVR32_EPTCTLENB(ep_no),
		    AVR32_EPTCTL_EPT_ENABL);
	}
}