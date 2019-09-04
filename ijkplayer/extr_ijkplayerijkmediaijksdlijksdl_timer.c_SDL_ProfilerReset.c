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
struct TYPE_4__ {int max_sample; } ;
typedef  TYPE_1__ SDL_Profiler ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SDL_ProfilerReset(SDL_Profiler* profiler, int max_sample)
{
    memset(profiler, 0, sizeof(SDL_Profiler));
    if (max_sample < 0)
        profiler->max_sample = 3;
    else
        profiler->max_sample = max_sample;
}