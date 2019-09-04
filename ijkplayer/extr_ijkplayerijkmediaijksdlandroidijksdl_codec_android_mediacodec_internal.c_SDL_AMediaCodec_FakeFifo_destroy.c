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
struct TYPE_5__ {int /*<<< orphan*/  wakeup_dequeue_cond; int /*<<< orphan*/  wakeup_enqueue_cond; scalar_t__ mutex; } ;
typedef  TYPE_1__ SDL_AMediaCodec_FakeFifo ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMediaCodec_FakeFifo_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_DestroyCondP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_DestroyMutexP (scalar_t__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SDL_AMediaCodec_FakeFifo_destroy(SDL_AMediaCodec_FakeFifo *fifo)
{
    if (!fifo)
        return;

    if (fifo->mutex)
        SDL_AMediaCodec_FakeFifo_abort(fifo);

    SDL_DestroyMutexP(&fifo->mutex);
    SDL_DestroyCondP(&fifo->wakeup_enqueue_cond);
    SDL_DestroyCondP(&fifo->wakeup_dequeue_cond);

    memset(fifo, 0, sizeof(SDL_AMediaCodec_FakeFifo));
}