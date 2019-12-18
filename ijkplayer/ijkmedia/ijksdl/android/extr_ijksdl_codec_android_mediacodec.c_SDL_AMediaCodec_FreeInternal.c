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
struct TYPE_5__ {scalar_t__ mutex; struct TYPE_5__* opaque; struct TYPE_5__* common; int /*<<< orphan*/  fake_fifo; } ;
typedef  TYPE_1__ SDL_AMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMediaCodec_FakeFifo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_DestroyMutexP (scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SDL_AMediaCodec_FreeInternal(SDL_AMediaCodec *acodec)
{
    if (!acodec)
        return;

    if (acodec->common) {
        SDL_AMediaCodec_FakeFifo_destroy(&acodec->common->fake_fifo);
        free(acodec->common);
    }

    free(acodec->opaque);

    if (acodec->mutex)
        SDL_DestroyMutexP(&acodec->mutex);

    memset(acodec, 0, sizeof(SDL_AMediaCodec));
    free(acodec);
}