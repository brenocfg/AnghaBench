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
typedef  int uint16_t ;
struct audio_params {int rate; int channels; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_S16_LE ; 
 int /*<<< orphan*/  AFMT_S24_LE ; 
 int /*<<< orphan*/  AFMT_S32_LE ; 
 int /*<<< orphan*/  AFMT_U8 ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int HDA_CODEC_FMT_BASE_MASK ; 
#define  HDA_CODEC_FMT_BITS_16 134 
#define  HDA_CODEC_FMT_BITS_24 133 
#define  HDA_CODEC_FMT_BITS_32 132 
#define  HDA_CODEC_FMT_BITS_8 131 
 int HDA_CODEC_FMT_BITS_MASK ; 
 int HDA_CODEC_FMT_CHAN_MASK ; 
 int HDA_CODEC_FMT_DIV_MASK ; 
 int HDA_CODEC_FMT_DIV_SHIFT ; 
#define  HDA_CODEC_FMT_MULT_2 130 
#define  HDA_CODEC_FMT_MULT_3 129 
#define  HDA_CODEC_FMT_MULT_4 128 
 int HDA_CODEC_FMT_MULT_MASK ; 
 int /*<<< orphan*/  assert (struct audio_params*) ; 

__attribute__((used)) static int
hda_codec_parse_format(uint16_t fmt, struct audio_params *params)
{
	uint8_t div = 0;

	assert(params);

	/* Compute the Sample Rate */
	params->rate = (fmt & HDA_CODEC_FMT_BASE_MASK) ? 44100 : 48000;

	switch (fmt & HDA_CODEC_FMT_MULT_MASK) {
	case HDA_CODEC_FMT_MULT_2:
		params->rate *= 2;
		break;
	case HDA_CODEC_FMT_MULT_3:
		params->rate *= 3;
		break;
	case HDA_CODEC_FMT_MULT_4:
		params->rate *= 4;
		break;
	}

	div = (fmt >> HDA_CODEC_FMT_DIV_SHIFT) & HDA_CODEC_FMT_DIV_MASK;
	params->rate /= (div + 1);

	/* Compute the Bits per Sample */
	switch (fmt & HDA_CODEC_FMT_BITS_MASK) {
	case HDA_CODEC_FMT_BITS_8:
		params->format = AFMT_U8;
		break;
	case HDA_CODEC_FMT_BITS_16:
		params->format = AFMT_S16_LE;
		break;
	case HDA_CODEC_FMT_BITS_24:
		params->format = AFMT_S24_LE;
		break;
	case HDA_CODEC_FMT_BITS_32:
		params->format = AFMT_S32_LE;
		break;
	default:
		DPRINTF("Unknown format bits: 0x%x\n",
		    fmt & HDA_CODEC_FMT_BITS_MASK);
		return (-1);
	}

	/* Compute the Number of Channels */
	params->channels = (fmt & HDA_CODEC_FMT_CHAN_MASK) + 1;

	return (0);
}