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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  SDL_VoutOverlay ;
typedef  TYPE_1__ SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 int func_display_overlay_l (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int func_display_overlay(SDL_Vout *vout, SDL_VoutOverlay *overlay)
{
    SDL_LockMutex(vout->mutex);
    int retval = func_display_overlay_l(vout, overlay);
    SDL_UnlockMutex(vout->mutex);
    return retval;
}