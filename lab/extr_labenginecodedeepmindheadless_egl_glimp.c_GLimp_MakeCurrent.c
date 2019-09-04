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
 int /*<<< orphan*/  CHECK_EGL_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_context ; 
 int /*<<< orphan*/  egl_display ; 
 int /*<<< orphan*/  egl_surface ; 

void GLimp_MakeCurrent(void) {
  CHECK_EGL_SUCCESS(eglMakeCurrent(egl_display, egl_surface, egl_surface,
                                   egl_context));
}