#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mutex; scalar_t__ size; scalar_t__ end; scalar_t__ begin; scalar_t__ should_abort; } ;
typedef  TYPE_1__ SDL_AMediaCodec_FakeFifo ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 

void SDL_AMediaCodec_FakeFifo_flush(SDL_AMediaCodec_FakeFifo *fifo)
{
    if (fifo->should_abort)
        return;

    SDL_LockMutex(fifo->mutex);
    fifo->begin = 0;
    fifo->end   = 0;
    fifo->size  = 0;
    SDL_UnlockMutex(fifo->mutex);
}