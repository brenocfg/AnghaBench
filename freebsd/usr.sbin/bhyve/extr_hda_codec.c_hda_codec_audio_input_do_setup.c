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
struct hda_codec_stream {int /*<<< orphan*/  fmt; struct audio* aud; } ;
struct hda_codec_softc {struct hda_codec_stream* streams; } ;
struct audio_params {int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; } ;
struct audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t HDA_CODEC_STREAM_INPUT ; 
 int audio_set_params (struct audio*,struct audio_params*) ; 
 int hda_codec_parse_format (int /*<<< orphan*/ ,struct audio_params*) ; 

__attribute__((used)) static int
hda_codec_audio_input_do_setup(void *arg)
{
	struct hda_codec_softc *sc = (struct hda_codec_softc *)arg;
	struct hda_codec_stream *st = NULL;
	struct audio *aud = NULL;
	struct audio_params params;
	int err;

	st = &sc->streams[HDA_CODEC_STREAM_INPUT];
	aud = st->aud;

	err = hda_codec_parse_format(st->fmt, &params);
	if (err)
		return (-1);

	DPRINTF("rate: %d, channels: %d, format: 0x%x\n",
	    params.rate, params.channels, params.format);

	return (audio_set_params(aud, &params));
}