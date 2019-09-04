#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* opaque; } ;
struct TYPE_7__ {scalar_t__ mutex; } ;
typedef  TYPE_1__ SDL_VoutOverlay_Opaque ;
typedef  TYPE_2__ SDL_VoutOverlay ;

/* Variables and functions */
 int /*<<< orphan*/  AMCTRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (scalar_t__) ; 
 int /*<<< orphan*/  SDL_VoutOverlay_FreeInternal (TYPE_2__*) ; 
 int /*<<< orphan*/  overlay_unref (TYPE_2__*) ; 

__attribute__((used)) static void overlay_free_l(SDL_VoutOverlay *overlay)
{
    AMCTRACE("SDL_Overlay(mediacodec): overlay_free_l(%p)\n", overlay);
    if (!overlay)
        return;

    SDL_VoutOverlay_Opaque *opaque = overlay->opaque;
    if (!opaque)
        return;

    overlay_unref(overlay);

    if (opaque->mutex)
        SDL_DestroyMutex(opaque->mutex);

    SDL_VoutOverlay_FreeInternal(overlay);
}