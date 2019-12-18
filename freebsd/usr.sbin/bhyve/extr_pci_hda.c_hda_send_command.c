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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct hda_softc {struct hda_codec_inst** codecs; } ;
struct hda_codec_inst {struct hda_codec_class* codec; } ;
struct hda_codec_class {int (* command ) (struct hda_codec_inst*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int HDA_CMD_CAD_SHIFT ; 
 int /*<<< orphan*/  assert (struct hda_codec_class*) ; 
 int stub1 (struct hda_codec_inst*,int) ; 

__attribute__((used)) static int
hda_send_command(struct hda_softc *sc, uint32_t verb)
{
	struct hda_codec_inst *hci = NULL;
	struct hda_codec_class *codec = NULL;
	uint8_t cad = (verb >> HDA_CMD_CAD_SHIFT) & 0x0f;

	hci = sc->codecs[cad];
	if (!hci)
		return (-1);

	DPRINTF("cad: 0x%x verb: 0x%x\n", cad, verb);

	codec = hci->codec;
	assert(codec);

	if (!codec->command) {
		DPRINTF("This codec does not implement the command function\n");
		return (-1);
	}

	return (codec->command(hci, verb));
}