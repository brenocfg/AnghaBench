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
struct hda_codec_cmd_ctl {int dummy; } ;
struct hda_softc {struct hda_codec_cmd_ctl rirb; } ;

/* Variables and functions */
 int HDAC_RIRBCTL_RIRBDMAEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int hda_get_reg_by_offset (struct hda_softc*,int) ; 
 int hda_rirb_start (struct hda_softc*) ; 
 int /*<<< orphan*/  memset (struct hda_codec_cmd_ctl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hda_set_rirbctl(struct hda_softc *sc, uint32_t offset, uint32_t old)
{
	uint32_t value = hda_get_reg_by_offset(sc, offset);
	int err;
	struct hda_codec_cmd_ctl *rirb = NULL;

	if (value & HDAC_RIRBCTL_RIRBDMAEN) {
		err = hda_rirb_start(sc);
		assert(!err);
	} else {
		rirb = &sc->rirb;
		memset(rirb, 0, sizeof(*rirb));
	}
}