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
typedef  TYPE_1__ SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateMutex () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* mallocz (size_t) ; 

__attribute__((used)) inline static SDL_AMediaFormat *SDL_AMediaFormat_CreateInternal(size_t opaque_size)
{
    SDL_AMediaFormat *aformat = (SDL_AMediaFormat*) mallocz(sizeof(SDL_AMediaFormat));
    if (!aformat)
        return NULL;

    aformat->opaque = mallocz(opaque_size);
    if (!aformat->opaque) {
        free(aformat);
        return NULL;
    }

    aformat->mutex = SDL_CreateMutex();
    if (aformat->mutex == NULL) {
        free(aformat->opaque);
        free(aformat);
        return NULL;
    }

    return aformat;
}