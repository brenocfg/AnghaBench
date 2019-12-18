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
struct hdaa_devinfo {int /*<<< orphan*/  nid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int APPLE_INTEL_MAC ; 
 int /*<<< orphan*/  HDA_CMD_12BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
#define  HDA_CODEC_ALC1150 137 
 int HDA_CODEC_ALC255 ; 
 int HDA_CODEC_ALC256 ; 
 int HDA_CODEC_ALC269 ; 
#define  HDA_CODEC_VT1708S_0 136 
#define  HDA_CODEC_VT1708S_1 135 
#define  HDA_CODEC_VT1708S_2 134 
#define  HDA_CODEC_VT1708S_3 133 
#define  HDA_CODEC_VT1708S_4 132 
#define  HDA_CODEC_VT1708S_5 131 
#define  HDA_CODEC_VT1708S_6 130 
#define  HDA_CODEC_VT1708S_7 129 
#define  HDA_CODEC_VT1818S 128 
 int /*<<< orphan*/  hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdaa_card_id (struct hdaa_devinfo*) ; 
 int hdaa_codec_id (struct hdaa_devinfo*) ; 
 int hdaa_read_coef (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdaa_write_coef (int /*<<< orphan*/ ,int,int,int) ; 

void
hdaa_patch_direct(struct hdaa_devinfo *devinfo)
{
	device_t dev = devinfo->dev;
	uint32_t id, subid, val;

	id = hdaa_codec_id(devinfo);
	subid = hdaa_card_id(devinfo);

	switch (id) {
	case HDA_CODEC_VT1708S_0:
	case HDA_CODEC_VT1708S_1:
	case HDA_CODEC_VT1708S_2:
	case HDA_CODEC_VT1708S_3:
	case HDA_CODEC_VT1708S_4:
	case HDA_CODEC_VT1708S_5:
	case HDA_CODEC_VT1708S_6:
	case HDA_CODEC_VT1708S_7:
		/* Enable Mic Boost Volume controls. */
		hda_command(dev, HDA_CMD_12BIT(0, devinfo->nid,
		    0xf98, 0x01));
		/* Fall though */
	case HDA_CODEC_VT1818S:
		/* Don't bypass mixer. */
		hda_command(dev, HDA_CMD_12BIT(0, devinfo->nid,
		    0xf88, 0xc0));
		break;
	case HDA_CODEC_ALC1150:
		if (subid == 0xd9781462) {
			/* Too low volume on MSI H170 GAMING M3. */
			hdaa_write_coef(dev, 0x20, 0x07, 0x7cb);
		}
		break;
	}
	if (id == HDA_CODEC_ALC255 || id == HDA_CODEC_ALC256) {
		val = hdaa_read_coef(dev, 0x20, 0x46);
		hdaa_write_coef(dev, 0x20, 0x46, val|0x3000);
	}
	if (subid == APPLE_INTEL_MAC)
		hda_command(dev, HDA_CMD_12BIT(0, devinfo->nid,
		    0x7e7, 0));
	if (id == HDA_CODEC_ALC269) {
		if (subid == 0x16e31043 || subid == 0x831a1043 ||
		    subid == 0x834a1043 || subid == 0x83981043 ||
		    subid == 0x83ce1043) {
			/*
			 * The ditital mics on some Asus laptops produce
			 * differential signals instead of expected stereo.
			 * That results in silence if downmix it to mono.
			 * To workaround, make codec to handle signal as mono.
			 */
			val = hdaa_read_coef(dev, 0x20, 0x07);
			hdaa_write_coef(dev, 0x20, 0x07, val|0x80);
		}
		if (subid == 0x15171043) {
			/* Increase output amp on ASUS UX31A by +5dB. */
			hdaa_write_coef(dev, 0x20, 0x12, 0x2800);
		}
	}
}