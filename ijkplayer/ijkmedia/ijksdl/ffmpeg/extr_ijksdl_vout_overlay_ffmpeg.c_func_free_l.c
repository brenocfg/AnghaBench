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
struct TYPE_7__ {TYPE_1__* opaque; } ;
struct TYPE_6__ {scalar_t__ mutex; scalar_t__ frame_buffer; scalar_t__ linked_frame; scalar_t__ managed_frame; int /*<<< orphan*/  img_convert_ctx; } ;
typedef  TYPE_1__ SDL_VoutOverlay_Opaque ;
typedef  TYPE_2__ SDL_VoutOverlay ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (scalar_t__) ; 
 int /*<<< orphan*/  SDL_VoutOverlay_FreeInternal (TYPE_2__*) ; 
 int /*<<< orphan*/  av_buffer_unref (scalar_t__*) ; 
 int /*<<< orphan*/  av_frame_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_frame_unref (scalar_t__) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void func_free_l(SDL_VoutOverlay *overlay)
{
    ALOGE("SDL_Overlay(ffmpeg): overlay_free_l(%p)\n", overlay);
    if (!overlay)
        return;

    SDL_VoutOverlay_Opaque *opaque = overlay->opaque;
    if (!opaque)
        return;

    sws_freeContext(opaque->img_convert_ctx);

    if (opaque->managed_frame)
        av_frame_free(&opaque->managed_frame);

    if (opaque->linked_frame) {
        av_frame_unref(opaque->linked_frame);
        av_frame_free(&opaque->linked_frame);
    }

    if (opaque->frame_buffer)
        av_buffer_unref(&opaque->frame_buffer);

    if (opaque->mutex)
        SDL_DestroyMutex(opaque->mutex);

    SDL_VoutOverlay_FreeInternal(overlay);
}