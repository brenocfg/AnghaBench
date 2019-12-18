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
typedef  int /*<<< orphan*/  uint32_t ;
struct hdmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INFOFRAME_CTRL_ENABLE ; 
 int /*<<< orphan*/  GENERIC_CTRL_AUDIO ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_GENERIC_CTRL ; 
 int /*<<< orphan*/  RD4 (struct hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audio_disable(struct hdmi_softc *sc) {
	uint32_t val;

	/* Disable audio */
	val = RD4(sc,  HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
	val &= ~GENERIC_CTRL_AUDIO;
	WR4(sc, HDMI_NV_PDISP_HDMI_GENERIC_CTRL, val);

	/* Disable audio infoframes */
	val = RD4(sc,  HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL);
	val &= ~AUDIO_INFOFRAME_CTRL_ENABLE;
	WR4(sc, HDMI_NV_PDISP_HDMI_AUDIO_INFOFRAME_CTRL, val);
}