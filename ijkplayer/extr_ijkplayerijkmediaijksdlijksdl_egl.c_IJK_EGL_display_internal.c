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
struct TYPE_6__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  display; TYPE_1__* opaque; } ;
struct TYPE_5__ {int /*<<< orphan*/  renderer; } ;
typedef  int /*<<< orphan*/  SDL_VoutOverlay ;
typedef  TYPE_1__ IJK_EGL_Opaque ;
typedef  TYPE_2__ IJK_EGL ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 int /*<<< orphan*/  EGL_FALSE ; 
 int /*<<< orphan*/  EGL_TRUE ; 
 int /*<<< orphan*/  IJK_EGL_prepareRenderer (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IJK_GLES2_Renderer_renderOverlay (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static EGLBoolean IJK_EGL_display_internal(IJK_EGL* egl, EGLNativeWindowType window, SDL_VoutOverlay *overlay)
{
    IJK_EGL_Opaque *opaque = egl->opaque;

    if (!IJK_EGL_prepareRenderer(egl, overlay)) {
        ALOGE("[EGL] IJK_EGL_prepareRenderer failed\n");
        return EGL_FALSE;
    }

    if (!IJK_GLES2_Renderer_renderOverlay(opaque->renderer, overlay)) {
        ALOGE("[EGL] IJK_GLES2_render failed\n");
        return EGL_FALSE; 
    }

    eglSwapBuffers(egl->display, egl->surface);

    return EGL_TRUE;
}