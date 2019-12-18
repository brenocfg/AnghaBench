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
typedef  int uint8_t ;
struct hdmi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  audio_chans; } ;
struct hdmi_audio_infoframe {int /*<<< orphan*/  channels; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int AUDIO_INFOFRAME_CTRL_ENABLE ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_HEADER ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_SUBPACK0_HIGH ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_SUBPACK0_LOW ; 
 int /*<<< orphan*/  WR4 (struct hdmi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 scalar_t__ hdmi_audio_infoframe_pack (struct hdmi_audio_infoframe*,int*,int) ; 

__attribute__((used)) static void
audio_setup_infoframe(struct hdmi_softc *sc)
{
	struct hdmi_audio_infoframe frame;
	uint8_t buf[14], *hdr, *pb;
	ssize_t rv;


	rv = hdmi_audio_infoframe_init(&frame);
	frame.channels = sc->audio_chans;
	rv = hdmi_audio_infoframe_pack(&frame, buf, sizeof(buf));
	if (rv < 0) {
		device_printf(sc->dev, "Cannot pack audio infoframe\n");
		return;
	}
	hdr = buf + 0;
	pb = buf + 3;
	WR4(sc, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_HEADER,
	    (hdr[2] << 16) | (hdr[1] << 8) | (hdr[0] << 0));
	WR4(sc, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_SUBPACK0_LOW,
	    (pb[3] << 24) |(pb[2] << 16) | (pb[1] << 8) | (pb[0] << 0));
	WR4(sc, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_SUBPACK0_HIGH,
	    (pb[5] << 8) | (pb[4] << 0));

	WR4(sc, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL,
	   AUDIO_INFOFRAME_CTRL_ENABLE);
}