#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SDL_Vout ;
typedef  int /*<<< orphan*/  SDL_AMediaCodecBufferProxy ;

/* Variables and functions */
 int SDL_VoutAndroid_releaseBufferProxy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int SDL_VoutAndroid_releaseBufferProxyP(SDL_Vout *vout, SDL_AMediaCodecBufferProxy **proxy, bool render)
{
    int ret = 0;

    if (!proxy)
        return 0;

    ret = SDL_VoutAndroid_releaseBufferProxy(vout, *proxy, render);
    *proxy = NULL;
    return ret;
}