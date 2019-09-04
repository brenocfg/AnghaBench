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
typedef  TYPE_1__ SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateMutex () ; 
 TYPE_1__* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) inline static SDL_Vout *SDL_Vout_CreateInternal(size_t opaque_size)
{
    SDL_Vout *vout = (SDL_Vout*) calloc(1, sizeof(SDL_Vout));
    if (!vout)
        return NULL;

    vout->opaque = calloc(1, opaque_size);
    if (!vout->opaque) {
        free(vout);
        return NULL;
    }

    vout->mutex = SDL_CreateMutex();
    if (vout->mutex == NULL) {
        free(vout->opaque);
        free(vout);
        return NULL;
    }

    return vout;
}