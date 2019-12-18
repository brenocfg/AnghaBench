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
struct TYPE_3__ {scalar_t__ max_sample; int total_counter; int sample_elapsed; int sample_counter; int average_elapsed; float sample_per_seconds; int /*<<< orphan*/  total_elapsed; scalar_t__ begin_time; } ;
typedef  TYPE_1__ SDL_Profiler ;

/* Variables and functions */
 scalar_t__ SDL_GetTickHR () ; 

int64_t SDL_ProfilerEnd(SDL_Profiler* profiler)
{
    int64_t delta = SDL_GetTickHR() - profiler->begin_time;

    if (profiler->max_sample > 0) {
        profiler->total_elapsed += delta;
        profiler->total_counter += 1;

        profiler->sample_elapsed += delta;
        profiler->sample_counter  += 1;

        if (profiler->sample_counter > profiler->max_sample) {
            profiler->sample_elapsed -= profiler->average_elapsed;
            profiler->sample_counter -= 1;
        }

        if (profiler->sample_counter > 0) {
            profiler->average_elapsed = profiler->sample_elapsed / profiler->sample_counter;
        }
        if (profiler->sample_elapsed > 0) {
            profiler->sample_per_seconds = profiler->sample_counter * 1000.f / profiler->sample_elapsed;
        }
    }

    return delta;
}