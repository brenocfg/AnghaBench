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
struct TYPE_3__ {scalar_t__ context; scalar_t__ surface; scalar_t__ display; scalar_t__ window; } ;
typedef  TYPE_1__ IJK_EGL ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_FALSE ; 
 int /*<<< orphan*/  EGL_TRUE ; 

__attribute__((used)) static EGLBoolean IJK_EGL_isValid(IJK_EGL* egl)
{
    if (egl &&
        egl->window &&
        egl->display &&
        egl->surface &&
        egl->context) {
        return EGL_TRUE;
    }

    return EGL_FALSE;
}