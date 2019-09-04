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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ sample_range; scalar_t__ last_profile_tick; scalar_t__ last_profile_duration; scalar_t__ last_profile_quantity; int last_profile_speed; } ;
typedef  TYPE_1__ SDL_SpeedSampler2 ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GetTickHR () ; 
 int /*<<< orphan*/  llabs (scalar_t__) ; 

int64_t SDL_SpeedSampler2Add(SDL_SpeedSampler2 *sampler, int quantity)
{
    if (quantity < 0)
        return 0;

    int64_t sample_range  = sampler->sample_range;
    int64_t last_tick     = sampler->last_profile_tick;
    int64_t last_duration = sampler->last_profile_duration;
    int64_t last_quantity = sampler->last_profile_quantity;
    int64_t now           = (int64_t)SDL_GetTickHR();
    int64_t elapsed       = (int64_t)llabs(now - last_tick);
    if (elapsed < 0 || elapsed >= sample_range) {
        // overflow, reset to initialized state
        sampler->last_profile_tick     = now;
        sampler->last_profile_duration = sample_range;
        sampler->last_profile_quantity = quantity;
        sampler->last_profile_speed    = quantity * 1000 / sample_range;
        return sampler->last_profile_speed;
    }

    int64_t new_quantity = last_quantity + quantity;
    int64_t new_duration = last_duration + elapsed;
    if (new_duration > sample_range) {
        new_quantity = new_quantity * sample_range / new_duration;
        new_duration = sample_range;
    }

    sampler->last_profile_tick     = now;
    sampler->last_profile_duration = new_duration;
    sampler->last_profile_quantity = new_quantity;
    if (new_duration > 0)
        sampler->last_profile_speed = new_quantity * 1000 / new_duration;
    return sampler->last_profile_speed;
}