#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buffer_index; scalar_t__ acodec_serial; } ;
typedef  TYPE_1__ SDL_AMediaCodecBufferProxy ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SDL_AMediaCodecBufferProxy_reset(SDL_AMediaCodecBufferProxy *proxy)
{
    memset(proxy, 0, sizeof(SDL_AMediaCodecBufferProxy));
    proxy->buffer_index  = -1;
    proxy->acodec_serial = 0;
}