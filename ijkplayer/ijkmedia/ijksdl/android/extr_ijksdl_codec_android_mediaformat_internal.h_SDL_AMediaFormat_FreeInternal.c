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
struct TYPE_5__ {struct TYPE_5__* opaque; scalar_t__ mutex; } ;
typedef  TYPE_1__ SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyMutexP (scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) inline static void SDL_AMediaFormat_FreeInternal(SDL_AMediaFormat *aformat)
{
    if (!aformat)
        return;

    if (aformat->mutex) {
        SDL_DestroyMutexP(&aformat->mutex);
    }

    free(aformat->opaque);
    memset(aformat, 0, sizeof(SDL_AMediaFormat));
    free(aformat);
}