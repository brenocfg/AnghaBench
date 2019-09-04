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
typedef  TYPE_1__ SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMEDIA_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

sdl_amedia_status_t SDL_AMediaFormat_delete(SDL_AMediaFormat* aformat)
{
    if (!aformat)
        return SDL_AMEDIA_OK;
    assert(aformat->func_delete);
    return aformat->func_delete(aformat);
}