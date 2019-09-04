#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ IJK_EGL ;
typedef  int EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  eglQuerySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int IJK_EGL_getSurfaceWidth(IJK_EGL* egl)
{
    EGLint width = 0;
    if (!eglQuerySurface(egl->display, egl->surface, EGL_WIDTH, &width)) {
        ALOGE("[EGL] eglQuerySurface(EGL_WIDTH) returned error %d", eglGetError());
        return 0;
    }

    return width;
}