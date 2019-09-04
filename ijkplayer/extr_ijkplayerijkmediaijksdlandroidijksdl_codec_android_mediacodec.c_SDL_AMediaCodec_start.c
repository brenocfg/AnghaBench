#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sdl_amedia_status_t ;
struct TYPE_5__ {scalar_t__ (* func_start ) (TYPE_1__*) ;int is_started; } ;
typedef  TYPE_1__ SDL_AMediaCodec ;

/* Variables and functions */
 scalar_t__ SDL_AMEDIA_OK ; 
 int /*<<< orphan*/  assert (scalar_t__ (*) (TYPE_1__*)) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 

sdl_amedia_status_t SDL_AMediaCodec_start(SDL_AMediaCodec* acodec)
{
    assert(acodec->func_start);
    sdl_amedia_status_t amc_ret = acodec->func_start(acodec);
    if (amc_ret == SDL_AMEDIA_OK) {
        acodec->is_started = true;
    }
    return amc_ret;
}