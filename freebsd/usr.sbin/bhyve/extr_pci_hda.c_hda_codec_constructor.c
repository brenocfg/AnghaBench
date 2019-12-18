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
struct hda_softc {scalar_t__ codecs_no; struct hda_codec_inst** codecs; } ;
struct hda_codec_inst {scalar_t__ cad; struct hda_codec_class* codec; int /*<<< orphan*/ * hops; struct hda_softc* hda; } ;
struct hda_codec_class {int (* init ) (struct hda_codec_inst*,char const*,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ HDA_CODEC_MAX ; 
 struct hda_codec_inst* calloc (int,int) ; 
 int /*<<< orphan*/  hops ; 
 int stub1 (struct hda_codec_inst*,char const*,char const*,char const*) ; 

__attribute__((used)) static int
hda_codec_constructor(struct hda_softc *sc, struct hda_codec_class *codec,
    const char *play, const char *rec, const char *opts)
{
	struct hda_codec_inst *hci = NULL;

	if (sc->codecs_no >= HDA_CODEC_MAX)
		return (-1);

	hci = calloc(1, sizeof(struct hda_codec_inst));
	if (!hci)
		return (-1);

	hci->hda = sc;
	hci->hops = &hops;
	hci->cad = sc->codecs_no;
	hci->codec = codec;

	sc->codecs[sc->codecs_no++] = hci;

	if (!codec->init) {
		DPRINTF("This codec does not implement the init function\n");
		return (-1);
	}

	return (codec->init(hci, play, rec, opts));
}