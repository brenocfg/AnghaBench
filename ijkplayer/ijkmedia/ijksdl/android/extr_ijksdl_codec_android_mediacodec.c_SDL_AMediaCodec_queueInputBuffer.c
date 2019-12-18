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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sdl_amedia_status_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* func_queueInputBuffer ) (TYPE_2__*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ;TYPE_1__* common; } ;
struct TYPE_6__ {int /*<<< orphan*/  fake_fifo; } ;
typedef  TYPE_2__ SDL_AMediaCodec ;

/* Variables and functions */
 int AMEDIACODEC__BUFFER_FLAG_FAKE_FRAME ; 
 int /*<<< orphan*/  SDL_AMediaCodec_FakeFifo_queueInputBuffer (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (TYPE_2__*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int)) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 

sdl_amedia_status_t SDL_AMediaCodec_queueInputBuffer(SDL_AMediaCodec* acodec, size_t idx, off_t offset, size_t size, uint64_t time, uint32_t flags)
{
    assert(acodec->func_queueInputBuffer);
    if (flags & AMEDIACODEC__BUFFER_FLAG_FAKE_FRAME) {
        return SDL_AMediaCodec_FakeFifo_queueInputBuffer(&acodec->common->fake_fifo, idx, offset, size, time, flags);
    }

    return acodec->func_queueInputBuffer(acodec, idx, offset, size, time, flags);
}