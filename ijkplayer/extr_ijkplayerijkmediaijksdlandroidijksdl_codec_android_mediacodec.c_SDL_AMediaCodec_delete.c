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
typedef  int /*<<< orphan*/  sdl_amedia_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* func_delete ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ SDL_AMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMEDIA_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

sdl_amedia_status_t SDL_AMediaCodec_delete(SDL_AMediaCodec* acodec)
{
    if (!acodec)
        return SDL_AMEDIA_OK;

    assert(acodec->func_delete);
    return acodec->func_delete(acodec);
}