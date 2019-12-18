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
struct TYPE_5__ {struct TYPE_5__* opaque; int /*<<< orphan*/ * mutex; } ;
typedef  TYPE_1__ SDL_Aout ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateMutex () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* mallocz (size_t) ; 

__attribute__((used)) inline static SDL_Aout *SDL_Aout_CreateInternal(size_t opaque_size)
{
    SDL_Aout *aout = (SDL_Aout*) mallocz(sizeof(SDL_Aout));
    if (!aout)
        return NULL;

    aout->opaque = mallocz(opaque_size);
    if (!aout->opaque) {
        free(aout);
        return NULL;
    }

    aout->mutex = SDL_CreateMutex();
    if (aout->mutex == NULL) {
        free(aout->opaque);
        free(aout);
        return NULL;
    }

    return aout;
}