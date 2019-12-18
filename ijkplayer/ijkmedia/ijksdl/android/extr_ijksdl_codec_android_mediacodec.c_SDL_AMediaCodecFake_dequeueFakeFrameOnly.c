#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__* common; } ;
struct TYPE_4__ {int /*<<< orphan*/  fake_fifo; } ;
typedef  int /*<<< orphan*/  SDL_AMediaCodecBufferInfo ;
typedef  TYPE_2__ SDL_AMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMediaCodec_FakeFifo_dequeueOutputBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ssize_t SDL_AMediaCodecFake_dequeueFakeFrameOnly(SDL_AMediaCodec* acodec, SDL_AMediaCodecBufferInfo *info, int64_t timeoutUs)
{
    return SDL_AMediaCodec_FakeFifo_dequeueOutputBuffer(&acodec->common->fake_fifo, info, 0);
}