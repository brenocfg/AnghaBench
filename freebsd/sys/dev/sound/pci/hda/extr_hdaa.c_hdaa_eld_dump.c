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
typedef  int u_int ;
struct hdaa_widget {int* eld; int eld_len; int /*<<< orphan*/  nid; struct hdaa_devinfo* devinfo; } ;
struct hdaa_devinfo {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * HDA_HDMI_CODING_TYPES ; 
#define  HDA_HDMI_CODING_TYPE_AACLC 136 
#define  HDA_HDMI_CODING_TYPE_AC3 135 
#define  HDA_HDMI_CODING_TYPE_ATRAC 134 
#define  HDA_HDMI_CODING_TYPE_DTS 133 
#define  HDA_HDMI_CODING_TYPE_LPCM 132 
#define  HDA_HDMI_CODING_TYPE_MP3 131 
#define  HDA_HDMI_CODING_TYPE_MPEG1 130 
#define  HDA_HDMI_CODING_TYPE_MPEG2 129 
 int HDA_HDMI_CODING_TYPE_REF_CTX ; 
#define  HDA_HDMI_CODING_TYPE_WMAPRO 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
hdaa_eld_dump(struct hdaa_widget *w)
{
	struct hdaa_devinfo *devinfo = w->devinfo;
	device_t dev = devinfo->dev;
	uint8_t *sad;
	int len, mnl, i, sadc, fmt;

	if (w->eld == NULL || w->eld_len < 4)
		return;
	device_printf(dev,
	    "ELD nid=%d: ELD_Ver=%u Baseline_ELD_Len=%u\n",
	    w->nid, w->eld[0] >> 3, w->eld[2]);
	if ((w->eld[0] >> 3) != 0x02)
		return;
	len = min(w->eld_len, (u_int)w->eld[2] * 4);
	mnl = w->eld[4] & 0x1f;
	device_printf(dev,
	    "ELD nid=%d: CEA_EDID_Ver=%u MNL=%u\n",
	    w->nid, w->eld[4] >> 5, mnl);
	sadc = w->eld[5] >> 4;
	device_printf(dev,
	    "ELD nid=%d: SAD_Count=%u Conn_Type=%u S_AI=%u HDCP=%u\n",
	    w->nid, sadc, (w->eld[5] >> 2) & 0x3,
	    (w->eld[5] >> 1) & 0x1, w->eld[5] & 0x1);
	device_printf(dev,
	    "ELD nid=%d: Aud_Synch_Delay=%ums\n",
	    w->nid, w->eld[6] * 2);
	device_printf(dev,
	    "ELD nid=%d: Channels=0x%b\n",
	    w->nid, w->eld[7],
	    "\020\07RLRC\06FLRC\05RC\04RLR\03FC\02LFE\01FLR");
	device_printf(dev,
	    "ELD nid=%d: Port_ID=0x%02x%02x%02x%02x%02x%02x%02x%02x\n",
	    w->nid, w->eld[8], w->eld[9], w->eld[10], w->eld[11],
	    w->eld[12], w->eld[13], w->eld[14], w->eld[15]);
	device_printf(dev,
	    "ELD nid=%d: Manufacturer_Name=0x%02x%02x\n",
	    w->nid, w->eld[16], w->eld[17]);
	device_printf(dev,
	    "ELD nid=%d: Product_Code=0x%02x%02x\n",
	    w->nid, w->eld[18], w->eld[19]);
	device_printf(dev,
	    "ELD nid=%d: Monitor_Name_String='%.*s'\n",
	    w->nid, mnl, &w->eld[20]);
	for (i = 0; i < sadc; i++) {
		sad = &w->eld[20 + mnl + i * 3];
		fmt = (sad[0] >> 3) & 0x0f;
		if (fmt == HDA_HDMI_CODING_TYPE_REF_CTX) {
			fmt = (sad[2] >> 3) & 0x1f;
			if (fmt < 1 || fmt > 3)
				fmt = 0;
			else
				fmt += 14;
		}
		device_printf(dev,
		    "ELD nid=%d: %s %dch freqs=0x%b",
		    w->nid, HDA_HDMI_CODING_TYPES[fmt], (sad[0] & 0x07) + 1,
		    sad[1], "\020\007192\006176\00596\00488\00348\00244\00132");
		switch (fmt) {
		case HDA_HDMI_CODING_TYPE_LPCM:
			printf(" sizes=0x%b",
			    sad[2] & 0x07, "\020\00324\00220\00116");
			break;
		case HDA_HDMI_CODING_TYPE_AC3:
		case HDA_HDMI_CODING_TYPE_MPEG1:
		case HDA_HDMI_CODING_TYPE_MP3:
		case HDA_HDMI_CODING_TYPE_MPEG2:
		case HDA_HDMI_CODING_TYPE_AACLC:
		case HDA_HDMI_CODING_TYPE_DTS:
		case HDA_HDMI_CODING_TYPE_ATRAC:
			printf(" max_bitrate=%d", sad[2] * 8000);
			break;
		case HDA_HDMI_CODING_TYPE_WMAPRO:
			printf(" profile=%d", sad[2] & 0x07);
			break;
		}
		printf("\n");
	}
}