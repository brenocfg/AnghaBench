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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_11KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_16BIT (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_16KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_176KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_192KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_20BIT (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_22KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_24BIT (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_32BIT (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_32KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_44KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_88KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_8BIT (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_8KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_PCM_SIZE_RATE_96KHZ (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_STREAM_FORMATS_AC3 (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_STREAM_FORMATS_FLOAT32 (scalar_t__) ; 
 scalar_t__ HDA_PARAM_SUPP_STREAM_FORMATS_PCM (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
hdaa_dump_audio_formats(device_t dev, uint32_t fcap, uint32_t pcmcap)
{
	uint32_t cap;

	cap = fcap;
	if (cap != 0) {
		device_printf(dev, "     Stream cap: 0x%08x", cap);
		if (HDA_PARAM_SUPP_STREAM_FORMATS_AC3(cap))
			printf(" AC3");
		if (HDA_PARAM_SUPP_STREAM_FORMATS_FLOAT32(cap))
			printf(" FLOAT32");
		if (HDA_PARAM_SUPP_STREAM_FORMATS_PCM(cap))
			printf(" PCM");
		printf("\n");
	}
	cap = pcmcap;
	if (cap != 0) {
		device_printf(dev, "        PCM cap: 0x%08x", cap);
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_8BIT(cap))
			printf(" 8");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_16BIT(cap))
			printf(" 16");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_20BIT(cap))
			printf(" 20");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_24BIT(cap))
			printf(" 24");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_32BIT(cap))
			printf(" 32");
		printf(" bits,");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_8KHZ(cap))
			printf(" 8");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_11KHZ(cap))
			printf(" 11");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_16KHZ(cap))
			printf(" 16");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_22KHZ(cap))
			printf(" 22");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_32KHZ(cap))
			printf(" 32");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_44KHZ(cap))
			printf(" 44");
		printf(" 48");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_88KHZ(cap))
			printf(" 88");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_96KHZ(cap))
			printf(" 96");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_176KHZ(cap))
			printf(" 176");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_192KHZ(cap))
			printf(" 192");
		printf(" KHz\n");
	}
}