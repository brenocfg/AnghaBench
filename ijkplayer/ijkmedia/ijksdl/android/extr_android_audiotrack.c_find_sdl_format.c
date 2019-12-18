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
struct TYPE_4__ {int android_format; int /*<<< orphan*/  sdl_format; } ;
typedef  int /*<<< orphan*/  SDL_AudioFormat ;
typedef  TYPE_1__ AudioFormatMapEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INVALID ; 
 int NELEM (TYPE_1__*) ; 
 TYPE_1__* g_audio_format_map ; 

__attribute__((used)) static SDL_AudioFormat find_sdl_format(int android_format)
{
    for (int i = 0; i < NELEM(g_audio_format_map); ++i) {
        AudioFormatMapEntry *entry = &g_audio_format_map[i];
        if (entry->android_format == android_format)
            return entry->sdl_format;
    }
    return AUDIO_INVALID;
}