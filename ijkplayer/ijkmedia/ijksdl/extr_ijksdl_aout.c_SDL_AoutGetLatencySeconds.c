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
struct TYPE_4__ {double (* func_get_latency_seconds ) (TYPE_1__*) ;double minimal_latency_seconds; } ;
typedef  TYPE_1__ SDL_Aout ;

/* Variables and functions */
 double stub1 (TYPE_1__*) ; 

double SDL_AoutGetLatencySeconds(SDL_Aout *aout)
{
    if (!aout)
        return 0;

    if (aout->func_get_latency_seconds)
        return aout->func_get_latency_seconds(aout);

    return aout->minimal_latency_seconds;
}