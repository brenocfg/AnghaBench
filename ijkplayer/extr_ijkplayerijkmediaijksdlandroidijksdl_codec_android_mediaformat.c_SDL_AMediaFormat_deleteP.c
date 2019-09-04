#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sdl_amedia_status_t ;
typedef  int /*<<< orphan*/  SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMEDIA_OK ; 
 int /*<<< orphan*/  SDL_AMediaFormat_delete (int /*<<< orphan*/ *) ; 

sdl_amedia_status_t SDL_AMediaFormat_deleteP(SDL_AMediaFormat** aformat)
{
    if (!aformat)
        return SDL_AMEDIA_OK;
    sdl_amedia_status_t amc_ret = SDL_AMediaFormat_delete(*aformat);
    *aformat = NULL;
    return amc_ret;
}