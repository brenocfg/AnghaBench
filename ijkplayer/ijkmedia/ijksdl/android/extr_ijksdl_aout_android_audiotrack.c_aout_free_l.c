#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  wakeup_mutex; int /*<<< orphan*/  wakeup_cond; scalar_t__ buffer_size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ SDL_Aout_Opaque ;
typedef  TYPE_2__ SDL_Aout ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_Aout_FreeInternal (TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_close_audio (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aout_free_l(SDL_Aout *aout)
{
    if (!aout)
        return;

    aout_close_audio(aout);

    SDL_Aout_Opaque *opaque = aout->opaque;
    if (opaque) {
        free(opaque->buffer);
        opaque->buffer = NULL;
        opaque->buffer_size = 0;

        SDL_DestroyCond(opaque->wakeup_cond);
        SDL_DestroyMutex(opaque->wakeup_mutex);
    }

    SDL_Aout_FreeInternal(aout);
}