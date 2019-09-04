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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sdl_amedia_status_t ;
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  SDL_AMediaFormat ;
typedef  int /*<<< orphan*/  SDL_AMediaCrypto ;
typedef  int /*<<< orphan*/  SDL_AMediaCodec ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMEDIA_OK ; 

__attribute__((used)) static sdl_amedia_status_t SDL_AMediaCodecDummy_configure_surface(
    JNIEnv*env,
    SDL_AMediaCodec* acodec,
    const SDL_AMediaFormat* aformat,
    jobject android_surface,
    SDL_AMediaCrypto *crypto,
    uint32_t flags)
{
    return SDL_AMEDIA_OK;
}