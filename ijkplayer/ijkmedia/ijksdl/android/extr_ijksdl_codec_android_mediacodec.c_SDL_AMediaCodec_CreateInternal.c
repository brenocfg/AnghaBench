#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* common; void* opaque; int /*<<< orphan*/ * mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  fake_fifo; } ;
typedef  int /*<<< orphan*/  SDL_AMediaCodec_Common ;
typedef  TYPE_2__ SDL_AMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMediaCodec_FakeFifo_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_AMediaCodec_FreeInternal (TYPE_2__*) ; 
 int /*<<< orphan*/ * SDL_CreateMutex () ; 
 void* mallocz (int) ; 

SDL_AMediaCodec *SDL_AMediaCodec_CreateInternal(size_t opaque_size)
{
    SDL_AMediaCodec *acodec = (SDL_AMediaCodec*) mallocz(sizeof(SDL_AMediaCodec));
    if (!acodec)
        return NULL;

    acodec->mutex = SDL_CreateMutex();
    if (acodec->mutex == NULL)
        goto fail;

    acodec->opaque = mallocz(opaque_size);
    if (!acodec->opaque)
        goto fail;

    acodec->common = mallocz(sizeof(SDL_AMediaCodec_Common));
    if (!acodec->common)
        goto fail;

    SDL_AMediaCodec_FakeFifo_init(&acodec->common->fake_fifo);

    return acodec;
fail:
    SDL_AMediaCodec_FreeInternal(acodec);
    return NULL;
}