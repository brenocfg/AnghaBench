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
typedef  int /*<<< orphan*/  SDL_VoutOverlay ;
typedef  int /*<<< orphan*/  SDL_Vout ;

/* Variables and functions */
#define  IJK_AV_PIX_FMT__ANDROID_MEDIACODEC 128 
 int /*<<< orphan*/ * SDL_VoutAMediaCodec_CreateOverlay (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SDL_VoutFFmpeg_CreateOverlay (int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SDL_VoutOverlay *func_create_overlay_l(int width, int height, int frame_format, SDL_Vout *vout)
{
    switch (frame_format) {
    case IJK_AV_PIX_FMT__ANDROID_MEDIACODEC:
        return SDL_VoutAMediaCodec_CreateOverlay(width, height, vout);
    default:
        return SDL_VoutFFmpeg_CreateOverlay(width, height, frame_format, vout);
    }
}