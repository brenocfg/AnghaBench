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
struct TYPE_6__ {scalar_t__ display; scalar_t__ surface; scalar_t__ context; TYPE_1__* opaque; } ;
struct TYPE_5__ {int /*<<< orphan*/  renderer; } ;
typedef  TYPE_2__ IJK_EGL ;

/* Variables and functions */
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  IJK_EGL_isValid (TYPE_2__*) ; 
 int /*<<< orphan*/  IJK_GLES2_Renderer_freeP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglDestroyContext (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglDestroySurface (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglMakeCurrent (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglReleaseThread () ; 
 int /*<<< orphan*/  eglTerminate (scalar_t__) ; 

void IJK_EGL_terminate(IJK_EGL* egl)
{
    if (!IJK_EGL_isValid(egl))
        return;

    if (egl->opaque)
        IJK_GLES2_Renderer_freeP(&egl->opaque->renderer);

    if (egl->display) {
        eglMakeCurrent(egl->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (egl->context)
            eglDestroyContext(egl->display, egl->context);
        if (egl->surface)
            eglDestroySurface(egl->display, egl->surface);
        eglTerminate(egl->display);
        eglReleaseThread(); // FIXME: call at thread exit
    }

    egl->context = EGL_NO_CONTEXT;
    egl->surface = EGL_NO_SURFACE;
    egl->display = EGL_NO_DISPLAY;
}