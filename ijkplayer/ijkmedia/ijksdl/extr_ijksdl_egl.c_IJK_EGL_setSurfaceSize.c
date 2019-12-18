#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ IJK_EGL ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,int) ; 
 int /*<<< orphan*/  ALOGI (char*,int,int,int,int) ; 
 int ANativeWindow_getFormat (int /*<<< orphan*/ ) ; 
 int ANativeWindow_setBuffersGeometry (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  EGL_FALSE ; 
 int /*<<< orphan*/  EGL_TRUE ; 
 void* IJK_EGL_getSurfaceHeight (TYPE_1__*) ; 
 void* IJK_EGL_getSurfaceWidth (TYPE_1__*) ; 
 int /*<<< orphan*/  IJK_EGL_isValid (TYPE_1__*) ; 

__attribute__((used)) static EGLBoolean IJK_EGL_setSurfaceSize(IJK_EGL* egl, int width, int height)
{
    if (!IJK_EGL_isValid(egl))
        return EGL_FALSE;

#ifdef __ANDROID__
    egl->width  = IJK_EGL_getSurfaceWidth(egl);
    egl->height = IJK_EGL_getSurfaceHeight(egl);

    if (width != egl->width || height != egl->height) {
        int format = ANativeWindow_getFormat(egl->window);
        ALOGI("ANativeWindow_setBuffersGeometry(w=%d,h=%d) -> (w=%d,h=%d);",
            egl->width, egl->height,
            width, height);
        int ret = ANativeWindow_setBuffersGeometry(egl->window, width, height, format);
        if (ret) {
            ALOGE("[EGL] ANativeWindow_setBuffersGeometry() returned error %d", ret);
            return EGL_FALSE;
        }

        egl->width  = IJK_EGL_getSurfaceWidth(egl);
        egl->height = IJK_EGL_getSurfaceHeight(egl);
        return (egl->width && egl->height) ? EGL_TRUE : EGL_FALSE;
    }

    return EGL_TRUE;
#else
    // FIXME: other platform?
#endif
    return EGL_FALSE;
}