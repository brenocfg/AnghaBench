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
typedef  int /*<<< orphan*/  Uint8 ;
struct TYPE_4__ {int android_channel; int /*<<< orphan*/  sdl_channel; } ;
typedef  TYPE_1__ AudioChannelMapEntry ;

/* Variables and functions */
 int NELEM (TYPE_1__*) ; 
 TYPE_1__* g_audio_channel_map ; 

__attribute__((used)) static Uint8 find_sdl_channel(int android_channel)
{
    for (int i = 0; i < NELEM(g_audio_channel_map); ++i) {
        AudioChannelMapEntry *entry = &g_audio_channel_map[i];
        if (entry->android_channel == android_channel)
            return entry->sdl_channel;
    }
    return 0;
}