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
struct TYPE_6__ {TYPE_1__* opaque; } ;
struct TYPE_5__ {int /*<<< orphan*/  renderer; } ;
typedef  TYPE_2__ IJK_EGL ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_EGL_terminate (TYPE_2__*) ; 

void IJK_EGL_releaseWindow(IJK_EGL* egl)
{
    if (!egl || !egl->opaque || !egl->opaque->renderer)
        return;

    IJK_EGL_terminate(egl);
}