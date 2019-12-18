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
struct dwc_hdmi_softc {int sc_has_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_hdmi_av_composer (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_clear_overflow (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_configure_audio (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_disable_overflow_interrupts (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_enable_video_path (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_init (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_tx_hdcp_config (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_video_packetize (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_video_sample (struct dwc_hdmi_softc*) ; 

__attribute__((used)) static int
dwc_hdmi_set_mode(struct dwc_hdmi_softc *sc)
{

	/* XXX */
	sc->sc_has_audio = 1;

	dwc_hdmi_disable_overflow_interrupts(sc);
	dwc_hdmi_av_composer(sc);
	dwc_hdmi_phy_init(sc);
	dwc_hdmi_enable_video_path(sc);
	dwc_hdmi_configure_audio(sc);
	/* TODO:  dwc_hdmi_config_avi(sc); */
	dwc_hdmi_video_packetize(sc);
	/* TODO:  dwc_hdmi_video_csc(sc); */
	dwc_hdmi_video_sample(sc);
	dwc_hdmi_tx_hdcp_config(sc);
	dwc_hdmi_clear_overflow(sc);

	return (0);
}