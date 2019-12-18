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
struct sbuf {int dummy; } ;

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
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
hdaa_dump_audio_formats_sb(struct sbuf *sb, uint32_t fcap, uint32_t pcmcap)
{
	uint32_t cap;

	cap = fcap;
	if (cap != 0) {
		sbuf_printf(sb, "     Stream cap: 0x%08x", cap);
		if (HDA_PARAM_SUPP_STREAM_FORMATS_AC3(cap))
			sbuf_printf(sb, " AC3");
		if (HDA_PARAM_SUPP_STREAM_FORMATS_FLOAT32(cap))
			sbuf_printf(sb, " FLOAT32");
		if (HDA_PARAM_SUPP_STREAM_FORMATS_PCM(cap))
			sbuf_printf(sb, " PCM");
		sbuf_printf(sb, "\n");
	}
	cap = pcmcap;
	if (cap != 0) {
		sbuf_printf(sb, "        PCM cap: 0x%08x", cap);
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_8BIT(cap))
			sbuf_printf(sb, " 8");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_16BIT(cap))
			sbuf_printf(sb, " 16");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_20BIT(cap))
			sbuf_printf(sb, " 20");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_24BIT(cap))
			sbuf_printf(sb, " 24");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_32BIT(cap))
			sbuf_printf(sb, " 32");
		sbuf_printf(sb, " bits,");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_8KHZ(cap))
			sbuf_printf(sb, " 8");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_11KHZ(cap))
			sbuf_printf(sb, " 11");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_16KHZ(cap))
			sbuf_printf(sb, " 16");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_22KHZ(cap))
			sbuf_printf(sb, " 22");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_32KHZ(cap))
			sbuf_printf(sb, " 32");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_44KHZ(cap))
			sbuf_printf(sb, " 44");
		sbuf_printf(sb, " 48");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_88KHZ(cap))
			sbuf_printf(sb, " 88");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_96KHZ(cap))
			sbuf_printf(sb, " 96");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_176KHZ(cap))
			sbuf_printf(sb, " 176");
		if (HDA_PARAM_SUPP_PCM_SIZE_RATE_192KHZ(cap))
			sbuf_printf(sb, " 192");
		sbuf_printf(sb, " KHz\n");
	}
}