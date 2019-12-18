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

/* Variables and functions */
 int /*<<< orphan*/  S_CodecRegister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * codecs ; 
 int /*<<< orphan*/  ogg_codec ; 
 int /*<<< orphan*/  opus_codec ; 
 int /*<<< orphan*/  wav_codec ; 

void S_CodecInit()
{
	codecs = NULL;

#ifdef USE_CODEC_OPUS
	S_CodecRegister(&opus_codec);
#endif

#ifdef USE_CODEC_VORBIS
	S_CodecRegister(&ogg_codec);
#endif

// Register wav codec last so that it is always tried first when a file extension was not found
	S_CodecRegister(&wav_codec);
}