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
typedef  int /*<<< orphan*/  sdl_amedia_status_t ;
struct TYPE_5__ {TYPE_1__* opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/  dummy_fifo; } ;
typedef  TYPE_2__ SDL_AMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMEDIA_OK ; 
 int /*<<< orphan*/  SDL_AMediaCodec_FakeFifo_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sdl_amedia_status_t SDL_AMediaCodecDummy_flush(SDL_AMediaCodec* acodec)
{
    SDL_AMediaCodec_FakeFifo_flush(&acodec->opaque->dummy_fifo);
    return SDL_AMEDIA_OK;
}