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
struct TYPE_7__ {int /*<<< orphan*/  display_overlay; int /*<<< orphan*/  (* free_l ) (TYPE_2__*) ;int /*<<< orphan*/  create_overlay; int /*<<< orphan*/ * opaque_class; TYPE_1__* opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  egl; int /*<<< orphan*/  overlay_pool; int /*<<< orphan*/  overlay_manager; int /*<<< orphan*/ * native_window; } ;
typedef  TYPE_1__ SDL_Vout_Opaque ;
typedef  TYPE_2__ SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_EGL_create () ; 
 scalar_t__ ISDL_Array__init (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* SDL_Vout_CreateInternal (int) ; 
 int /*<<< orphan*/  func_create_overlay ; 
 int /*<<< orphan*/  func_display_overlay ; 
 int /*<<< orphan*/  func_free_l (TYPE_2__*) ; 
 int /*<<< orphan*/  g_nativewindow_class ; 

SDL_Vout *SDL_VoutAndroid_CreateForANativeWindow()
{
    SDL_Vout *vout = SDL_Vout_CreateInternal(sizeof(SDL_Vout_Opaque));
    if (!vout)
        return NULL;

    SDL_Vout_Opaque *opaque = vout->opaque;
    opaque->native_window = NULL;
    if (ISDL_Array__init(&opaque->overlay_manager, 32))
        goto fail;
    if (ISDL_Array__init(&opaque->overlay_pool, 32))
        goto fail;

    opaque->egl = IJK_EGL_create();
    if (!opaque->egl)
        goto fail;

    vout->opaque_class    = &g_nativewindow_class;
    vout->create_overlay  = func_create_overlay;
    vout->free_l          = func_free_l;
    vout->display_overlay = func_display_overlay;

    return vout;
fail:
    func_free_l(vout);
    return NULL;
}