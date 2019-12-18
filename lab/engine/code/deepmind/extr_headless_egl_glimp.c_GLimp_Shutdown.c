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

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  RETURN_IF_EGL_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShutDownEGLSubsystem () ; 
 int /*<<< orphan*/  TerminateInitializedEGLDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_context ; 
 int /*<<< orphan*/  egl_display ; 
 int /*<<< orphan*/  egl_surface ; 

void GLimp_Shutdown(void) {
  RETURN_IF_EGL_ERROR(eglMakeCurrent(egl_display, EGL_NO_SURFACE,
                                     EGL_NO_SURFACE, EGL_NO_CONTEXT));
  RETURN_IF_EGL_ERROR(eglDestroySurface(egl_display, egl_surface));
  RETURN_IF_EGL_ERROR(eglDestroyContext(egl_display, egl_context));
  RETURN_IF_EGL_ERROR(TerminateInitializedEGLDisplay(egl_display));
  ShutDownEGLSubsystem();
}