#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int min_buffer_size; } ;
typedef  TYPE_1__ SDL_Android_AudioTrack ;

/* Variables and functions */

int SDL_Android_AudioTrack_get_min_buffer_size(SDL_Android_AudioTrack* atrack)
{
    return atrack->min_buffer_size;
}