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
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  MST_MSCWR2 ; 
 int /*<<< orphan*/  MST_MSCWR2_AC97_SPKROFF ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static void mst_audio_shutdown(struct snd_pcm_substream *substream, void *priv)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		MST_MSCWR2 |= MST_MSCWR2_AC97_SPKROFF;
}