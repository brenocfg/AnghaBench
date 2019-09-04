#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sdl_amedia_status_t ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_5__ {int is_configured; int is_started; int /*<<< orphan*/  (* func_configure_surface ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SDL_AMediaFormat ;
typedef  int /*<<< orphan*/  SDL_AMediaCrypto ;
typedef  TYPE_1__ SDL_AMediaCodec ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sdl_amedia_status_t SDL_AMediaCodec_configure_surface(
    JNIEnv*env,
    SDL_AMediaCodec* acodec,
    const SDL_AMediaFormat* aformat,
    jobject android_surface,
    SDL_AMediaCrypto *crypto,
    uint32_t flags)
{
    assert(acodec->func_configure_surface);
    sdl_amedia_status_t ret = acodec->func_configure_surface(env, acodec, aformat, android_surface, crypto, flags);
    acodec->is_configured = true;
    acodec->is_started    = false;
    return ret;
}