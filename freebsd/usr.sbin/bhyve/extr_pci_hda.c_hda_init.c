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
struct hda_softc {int dummy; } ;
struct hda_codec_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,char const*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct hda_softc* calloc (int,int) ; 
 int /*<<< orphan*/  dbg ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int hda_codec_constructor (struct hda_softc*,struct hda_codec_class*,char*,char*,int /*<<< orphan*/ *) ; 
 struct hda_codec_class* hda_find_codec_class (char*) ; 
 int hda_parse_config (char const*,char*,char*) ; 
 int /*<<< orphan*/  hda_reset_regs (struct hda_softc*) ; 

__attribute__((used)) static struct hda_softc *
hda_init(const char *opts)
{
	struct hda_softc *sc = NULL;
	struct hda_codec_class *codec = NULL;
	char play[64];
	char rec[64];
	int err, p, r;

#if DEBUG_HDA == 1
	dbg = fopen("/tmp/bhyve_hda.log", "w+");
#endif

	DPRINTF("opts: %s\n", opts);

	sc = calloc(1, sizeof(*sc));
	if (!sc)
		return (NULL);

	hda_reset_regs(sc);

	/*
	 * TODO search all the codecs declared in opts
	 * For now we play with one single codec
	 */
	codec = hda_find_codec_class("hda_codec");
	if (codec) {
		p = hda_parse_config(opts, "play=", play);
		r = hda_parse_config(opts, "rec=", rec);
		DPRINTF("play: %s rec: %s\n", play, rec);
		if (p | r) {
			err = hda_codec_constructor(sc, codec, p ?	\
				play : NULL, r ? rec : NULL, NULL);
			assert(!err);
		}
	}

	return (sc);
}