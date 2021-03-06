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
typedef  int /*<<< orphan*/  IJK_EGL ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_EGL_terminate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void IJK_EGL_free(IJK_EGL *egl)
{
    if (!egl)
        return;

    IJK_EGL_terminate(egl);

    memset(egl, 0, sizeof(IJK_EGL));
    free(egl);
}