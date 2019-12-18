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
struct hdmi_softc {int audio_freq; int audio_chans; int /*<<< orphan*/  hdmi_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_HDA_CODEC_SCRATCH0 ; 
 int RD4 (struct hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_disable (struct hdmi_softc*) ; 
 int /*<<< orphan*/  audio_enable (struct hdmi_softc*) ; 
 int audio_setup (struct hdmi_softc*) ; 

__attribute__((used)) static void
hda_intr(struct hdmi_softc *sc)
{
	uint32_t val;
	int rv;

	if (!sc->hdmi_mode)
		return;

	val = RD4(sc, HDMI_NV_PDISP_SOR_AUDIO_HDA_CODEC_SCRATCH0);
	if ((val & (1 << 30)) == 0) {
		audio_disable(sc);
		return;
	}

	/* XXX Move this to any header */
	/* Keep in sync with HDA */
	sc->audio_freq =  val & 0x00FFFFFF;
	sc->audio_chans = (val >> 24) & 0x0f;
	DRM_DEBUG_KMS("%d channel(s) at %dHz\n", sc->audio_chans,
	    sc->audio_freq);

	rv = audio_setup(sc);
	if (rv != 0) {
		audio_disable(sc);
		return;
	}

	audio_enable(sc);
}