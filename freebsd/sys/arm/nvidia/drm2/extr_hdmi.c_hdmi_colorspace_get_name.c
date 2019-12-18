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
typedef  enum hdmi_colorspace { ____Placeholder_hdmi_colorspace } hdmi_colorspace ;

/* Variables and functions */
#define  HDMI_COLORSPACE_IDO_DEFINED 135 
#define  HDMI_COLORSPACE_RESERVED4 134 
#define  HDMI_COLORSPACE_RESERVED5 133 
#define  HDMI_COLORSPACE_RESERVED6 132 
#define  HDMI_COLORSPACE_RGB 131 
#define  HDMI_COLORSPACE_YUV420 130 
#define  HDMI_COLORSPACE_YUV422 129 
#define  HDMI_COLORSPACE_YUV444 128 

__attribute__((used)) static const char *hdmi_colorspace_get_name(enum hdmi_colorspace colorspace)
{
	switch (colorspace) {
	case HDMI_COLORSPACE_RGB:
		return "RGB";
	case HDMI_COLORSPACE_YUV422:
		return "YCbCr 4:2:2";
	case HDMI_COLORSPACE_YUV444:
		return "YCbCr 4:4:4";
	case HDMI_COLORSPACE_YUV420:
		return "YCbCr 4:2:0";
	case HDMI_COLORSPACE_RESERVED4:
		return "Reserved (4)";
	case HDMI_COLORSPACE_RESERVED5:
		return "Reserved (5)";
	case HDMI_COLORSPACE_RESERVED6:
		return "Reserved (6)";
	case HDMI_COLORSPACE_IDO_DEFINED:
		return "IDO Defined";
	}
	return "Invalid";
}