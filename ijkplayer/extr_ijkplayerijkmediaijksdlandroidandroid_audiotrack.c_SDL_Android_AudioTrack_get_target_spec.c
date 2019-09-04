#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buffer_size_in_bytes; int /*<<< orphan*/  audio_format; int /*<<< orphan*/  channel_config; int /*<<< orphan*/  sample_rate_in_hz; } ;
struct TYPE_8__ {TYPE_2__ spec; } ;
struct TYPE_6__ {scalar_t__ padding; scalar_t__ silence; int /*<<< orphan*/  size; int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  freq; } ;
typedef  TYPE_1__ SDL_AudioSpec ;
typedef  TYPE_2__ SDL_Android_AudioTrack_Spec ;
typedef  TYPE_3__ SDL_Android_AudioTrack ;

/* Variables and functions */
 int /*<<< orphan*/  find_sdl_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_sdl_format (int /*<<< orphan*/ ) ; 

void SDL_Android_AudioTrack_get_target_spec(SDL_Android_AudioTrack *atrack, SDL_AudioSpec *sdl_spec)
{
    SDL_Android_AudioTrack_Spec *atrack_spec = &atrack->spec;

    sdl_spec->freq = atrack_spec->sample_rate_in_hz;
    sdl_spec->channels = find_sdl_channel(atrack_spec->channel_config);
    sdl_spec->format = find_sdl_format(atrack_spec->audio_format);
    sdl_spec->size = atrack_spec->buffer_size_in_bytes;
    sdl_spec->silence = 0;
    sdl_spec->padding = 0;
}