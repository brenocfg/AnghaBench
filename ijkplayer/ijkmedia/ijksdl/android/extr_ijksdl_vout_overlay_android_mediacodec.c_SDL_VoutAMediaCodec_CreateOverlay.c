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
struct TYPE_7__ {int w; int h; int is_private; int /*<<< orphan*/  func_fill_frame; int /*<<< orphan*/  unref; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  (* free_l ) (TYPE_2__*) ;int /*<<< orphan*/  pixels; int /*<<< orphan*/  pitches; int /*<<< orphan*/  format; int /*<<< orphan*/ * opaque_class; TYPE_1__* opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pixels; int /*<<< orphan*/  pitches; int /*<<< orphan*/ * buffer_proxy; int /*<<< orphan*/ * acodec; int /*<<< orphan*/ * vout; } ;
typedef  TYPE_1__ SDL_VoutOverlay_Opaque ;
typedef  TYPE_2__ SDL_VoutOverlay ;
typedef  int /*<<< orphan*/  SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 int /*<<< orphan*/  SDLTRACE (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_CreateMutex () ; 
 int /*<<< orphan*/  SDL_FCC__AMC ; 
 TYPE_2__* SDL_VoutOverlay_CreateInternal (int) ; 
 int /*<<< orphan*/  func_fill_frame ; 
 int /*<<< orphan*/  g_vout_overlay_amediacodec_class ; 
 int /*<<< orphan*/  overlay_free_l (TYPE_2__*) ; 
 int /*<<< orphan*/  overlay_lock ; 
 int /*<<< orphan*/  overlay_unlock ; 
 int /*<<< orphan*/  overlay_unref ; 

SDL_VoutOverlay *SDL_VoutAMediaCodec_CreateOverlay(int width, int height, SDL_Vout *vout)
{
    SDLTRACE("SDL_VoutAMediaCodec_CreateOverlay(w=%d, h=%d, fmt=_AMC vout=%p)\n",
        width, height, vout);
    SDL_VoutOverlay *overlay = SDL_VoutOverlay_CreateInternal(sizeof(SDL_VoutOverlay_Opaque));
    if (!overlay) {
        ALOGE("overlay allocation failed");
        return NULL;
    }

    SDL_VoutOverlay_Opaque *opaque = overlay->opaque;
    opaque->mutex         = SDL_CreateMutex();
    opaque->vout          = vout;
    opaque->acodec        = NULL;
    opaque->buffer_proxy  = NULL;

    overlay->opaque_class = &g_vout_overlay_amediacodec_class;
    overlay->format       = SDL_FCC__AMC;
    overlay->pitches      = opaque->pitches;
    overlay->pixels       = opaque->pixels;
    overlay->w            = width;
    overlay->h            = height;
    overlay->is_private   = 1;

    overlay->free_l       = overlay_free_l;
    overlay->lock         = overlay_lock;
    overlay->unlock       = overlay_unlock;
    overlay->unref        = overlay_unref;
    overlay->func_fill_frame = func_fill_frame;

    if (!opaque->mutex) {
        ALOGE("SDL_CreateMutex failed");
        goto fail;
    }

    return overlay;

fail:
    overlay_free_l(overlay);
    return NULL;
}