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
typedef  enum hdmi_quantization_range { ____Placeholder_hdmi_quantization_range } hdmi_quantization_range ;

/* Variables and functions */
#define  HDMI_QUANTIZATION_RANGE_DEFAULT 131 
#define  HDMI_QUANTIZATION_RANGE_FULL 130 
#define  HDMI_QUANTIZATION_RANGE_LIMITED 129 
#define  HDMI_QUANTIZATION_RANGE_RESERVED 128 

__attribute__((used)) static const char *
hdmi_quantization_range_get_name(enum hdmi_quantization_range qrange)
{
	switch (qrange) {
	case HDMI_QUANTIZATION_RANGE_DEFAULT:
		return "Default";
	case HDMI_QUANTIZATION_RANGE_LIMITED:
		return "Limited";
	case HDMI_QUANTIZATION_RANGE_FULL:
		return "Full";
	case HDMI_QUANTIZATION_RANGE_RESERVED:
		return "Reserved";
	}
	return "Invalid";
}