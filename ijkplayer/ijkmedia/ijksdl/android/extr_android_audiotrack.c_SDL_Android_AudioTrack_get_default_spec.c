#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mode; scalar_t__ buffer_size_in_bytes; int /*<<< orphan*/  audio_format; int /*<<< orphan*/  channel_config; scalar_t__ sample_rate_in_hz; int /*<<< orphan*/  stream_type; } ;
typedef  TYPE_1__ SDL_Android_AudioTrack_Spec ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_OUT_STEREO ; 
 int /*<<< orphan*/  ENCODING_PCM_16BIT ; 
 int /*<<< orphan*/  MODE_STREAM ; 
 int /*<<< orphan*/  STREAM_MUSIC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void SDL_Android_AudioTrack_get_default_spec(SDL_Android_AudioTrack_Spec *spec)
{
    assert(spec);
    spec->stream_type = STREAM_MUSIC;
    spec->sample_rate_in_hz = 0;
    spec->channel_config = CHANNEL_OUT_STEREO;
    spec->audio_format = ENCODING_PCM_16BIT;
    spec->buffer_size_in_bytes = 0;
    spec->mode = MODE_STREAM;
}