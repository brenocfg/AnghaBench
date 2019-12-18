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
struct hda_softc {int codecs_no; int /*<<< orphan*/  wall_clock_start; struct hda_codec_inst** codecs; } ;
struct hda_codec_inst {int /*<<< orphan*/  (* reset ) (struct hda_codec_inst*) ;struct hda_codec_inst* codec; } ;
struct hda_codec_class {int /*<<< orphan*/  (* reset ) (struct hda_codec_inst*) ;struct hda_codec_class* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct hda_codec_inst*) ; 
 int /*<<< orphan*/  hda_get_clock_ns () ; 
 int /*<<< orphan*/  hda_reset_regs (struct hda_softc*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec_inst*) ; 

__attribute__((used)) static void
hda_reset(struct hda_softc *sc)
{
	int i;
	struct hda_codec_inst *hci = NULL;
	struct hda_codec_class *codec = NULL;

	hda_reset_regs(sc);

	/* Reset each codec */
	for (i = 0; i < sc->codecs_no; i++) {
		hci = sc->codecs[i];
		assert(hci);

		codec = hci->codec;
		assert(codec);

		if (codec->reset)
			codec->reset(hci);
	}

	sc->wall_clock_start = hda_get_clock_ns();
}