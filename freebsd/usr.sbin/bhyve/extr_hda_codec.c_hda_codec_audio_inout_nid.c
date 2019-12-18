#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct hda_codec_stream {int fmt; int left_gain; int left_mute; int right_gain; int right_mute; int stream; int channel; TYPE_1__ actx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int HDA_CMD_GET_AMP_GAIN_MUTE_LEFT ; 
 int HDA_CMD_SET_AMP_GAIN_MUTE_LEFT ; 
 int HDA_CMD_SET_AMP_GAIN_MUTE_RIGHT ; 
#define  HDA_CMD_VERB_GET_AMP_GAIN_MUTE 133 
#define  HDA_CMD_VERB_GET_CONV_FMT 132 
#define  HDA_CMD_VERB_GET_CONV_STREAM_CHAN 131 
#define  HDA_CMD_VERB_SET_AMP_GAIN_MUTE 130 
#define  HDA_CMD_VERB_SET_CONV_FMT 129 
#define  HDA_CMD_VERB_SET_CONV_STREAM_CHAN 128 
 int HDA_CODEC_SET_AMP_GAIN_MUTE_GAIN_MASK ; 
 int HDA_CODEC_SET_AMP_GAIN_MUTE_MUTE ; 
 int /*<<< orphan*/  hda_audio_ctxt_stop (TYPE_1__*) ; 

__attribute__((used)) static uint32_t
hda_codec_audio_inout_nid(struct hda_codec_stream *st, uint16_t verb,
    uint16_t payload)
{
	uint32_t res = 0;
	uint8_t mute = 0;
	uint8_t gain = 0;

	DPRINTF("%s verb: 0x%x, payload, 0x%x\n", st->actx.name, verb, payload);

	switch (verb) {
	case HDA_CMD_VERB_GET_CONV_FMT:
		res = st->fmt;
		break;
	case HDA_CMD_VERB_SET_CONV_FMT:
		st->fmt = payload;
		break;
	case HDA_CMD_VERB_GET_AMP_GAIN_MUTE:
		if (payload & HDA_CMD_GET_AMP_GAIN_MUTE_LEFT) {
			res = st->left_gain | st->left_mute;
			DPRINTF("GET_AMP_GAIN_MUTE_LEFT: 0x%x\n", res);
		} else {
			res = st->right_gain | st->right_mute;
			DPRINTF("GET_AMP_GAIN_MUTE_RIGHT: 0x%x\n", res);
		}
		break;
	case HDA_CMD_VERB_SET_AMP_GAIN_MUTE:
		mute = payload & HDA_CODEC_SET_AMP_GAIN_MUTE_MUTE;
		gain = payload & HDA_CODEC_SET_AMP_GAIN_MUTE_GAIN_MASK;

		if (payload & HDA_CMD_SET_AMP_GAIN_MUTE_LEFT) {
			st->left_mute = mute;
			st->left_gain = gain;
			DPRINTF("SET_AMP_GAIN_MUTE_LEFT: \
			    mute: 0x%x gain: 0x%x\n", mute, gain);
		}

		if (payload & HDA_CMD_SET_AMP_GAIN_MUTE_RIGHT) {
			st->right_mute = mute;
			st->right_gain = gain;
			DPRINTF("SET_AMP_GAIN_MUTE_RIGHT: \
			    mute: 0x%x gain: 0x%x\n", mute, gain);
		}
		break;
	case HDA_CMD_VERB_GET_CONV_STREAM_CHAN:
		res = (st->stream << 4) | st->channel;
		break;
	case HDA_CMD_VERB_SET_CONV_STREAM_CHAN:
		st->channel = payload & 0x0f;
		st->stream = (payload >> 4) & 0x0f;
		DPRINTF("st->channel: 0x%x st->stream: 0x%x\n",
		    st->channel, st->stream);
		if (!st->stream)
			hda_audio_ctxt_stop(&st->actx);
		break;
	default:
		DPRINTF("Unknown VERB: 0x%x\n", verb);
		break;
	}

	return (res);
}