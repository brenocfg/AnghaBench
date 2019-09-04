#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* opaque; } ;
struct TYPE_4__ {int pause_on; int /*<<< orphan*/  wakeup_mutex; int /*<<< orphan*/  wakeup_cond; } ;
typedef  TYPE_1__ SDL_Aout_Opaque ;
typedef  TYPE_2__ SDL_Aout ;

/* Variables and functions */
 int /*<<< orphan*/  SDLTRACE (char*,int) ; 
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aout_pause_audio(SDL_Aout *aout, int pause_on)
{
    SDL_Aout_Opaque *opaque = aout->opaque;

    SDL_LockMutex(opaque->wakeup_mutex);
    SDLTRACE("aout_pause_audio(%d)", pause_on);
    opaque->pause_on = pause_on;
    if (!pause_on)
        SDL_CondSignal(opaque->wakeup_cond);
    SDL_UnlockMutex(opaque->wakeup_mutex);
}