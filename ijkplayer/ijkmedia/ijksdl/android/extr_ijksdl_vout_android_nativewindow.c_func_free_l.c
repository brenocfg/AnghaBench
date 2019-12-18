#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* opaque; } ;
struct TYPE_5__ {int /*<<< orphan*/  acodec; int /*<<< orphan*/  egl; int /*<<< orphan*/ * native_window; int /*<<< orphan*/  overlay_manager; int /*<<< orphan*/  overlay_pool; } ;
typedef  TYPE_1__ SDL_Vout_Opaque ;
typedef  TYPE_2__ SDL_Vout ;
typedef  int /*<<< orphan*/  SDL_AMediaCodecBufferProxy ;

/* Variables and functions */
 int /*<<< orphan*/  ANativeWindow_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IJK_EGL_freep (int /*<<< orphan*/ *) ; 
 scalar_t__ ISDL_Array__begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISDL_Array__clear (int /*<<< orphan*/ *) ; 
 scalar_t__ ISDL_Array__end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_AMediaCodecBufferProxy_destroyP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SDL_AMediaCodec_decreaseReferenceP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Vout_FreeInternal (TYPE_2__*) ; 

__attribute__((used)) static void func_free_l(SDL_Vout *vout)
{
    if (!vout)
        return;

    SDL_Vout_Opaque *opaque = vout->opaque;
    if (opaque) {
        SDL_AMediaCodecBufferProxy **begin = (SDL_AMediaCodecBufferProxy **)ISDL_Array__begin(&opaque->overlay_manager);
        SDL_AMediaCodecBufferProxy **end   = (SDL_AMediaCodecBufferProxy **)ISDL_Array__end(&opaque->overlay_manager);
        for (; begin < end; ++begin) {
            SDL_AMediaCodecBufferProxy_destroyP(begin);
        }
        ISDL_Array__clear(&opaque->overlay_pool);
        ISDL_Array__clear(&opaque->overlay_manager);

        if (opaque->native_window) {
            ANativeWindow_release(opaque->native_window);
            opaque->native_window = NULL;
        }

        IJK_EGL_freep(&opaque->egl);

        SDL_AMediaCodec_decreaseReferenceP(&opaque->acodec);
    }

    SDL_Vout_FreeInternal(vout);
}