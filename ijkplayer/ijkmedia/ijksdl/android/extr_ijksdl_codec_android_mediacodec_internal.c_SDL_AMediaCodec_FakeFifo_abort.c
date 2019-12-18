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
struct TYPE_3__ {int should_abort; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeup_dequeue_cond; int /*<<< orphan*/  wakeup_enqueue_cond; } ;
typedef  TYPE_1__ SDL_AMediaCodec_FakeFifo ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 

void SDL_AMediaCodec_FakeFifo_abort(SDL_AMediaCodec_FakeFifo *fifo)
{
    SDL_LockMutex(fifo->mutex);
    fifo->should_abort = 1;
    SDL_CondSignal(fifo->wakeup_enqueue_cond);
    SDL_CondSignal(fifo->wakeup_dequeue_cond);
    SDL_UnlockMutex(fifo->mutex);
}