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
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int sample_range; scalar_t__ last_profile_tick; } ;
typedef  TYPE_1__ SDL_SpeedSampler2 ;

/* Variables and functions */
 scalar_t__ SDL_GetTickHR () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SDL_SpeedSampler2Reset(SDL_SpeedSampler2 *sampler, int sample_range)
{
    memset(sampler, 0, sizeof(SDL_SpeedSampler2));
    sampler->sample_range      = sample_range;
    sampler->last_profile_tick = (int64_t)SDL_GetTickHR();
}