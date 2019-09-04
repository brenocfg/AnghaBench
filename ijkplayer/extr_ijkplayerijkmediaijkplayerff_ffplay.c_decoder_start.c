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
struct TYPE_3__ {int /*<<< orphan*/  decoder_tid; int /*<<< orphan*/  _decoder_tid; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ Decoder ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SDL_CreateThreadEx (int /*<<< orphan*/ *,int (*) (void*),void*,char const*) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_queue_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decoder_start(Decoder *d, int (*fn)(void *), void *arg, const char *name)
{
    packet_queue_start(d->queue);
    d->decoder_tid = SDL_CreateThreadEx(&d->_decoder_tid, fn, arg, name);
    if (!d->decoder_tid) {
        av_log(NULL, AV_LOG_ERROR, "SDL_CreateThread(): %s\n", SDL_GetError());
        return AVERROR(ENOMEM);
    }
    return 0;
}