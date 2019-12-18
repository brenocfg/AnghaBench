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
typedef  int /*<<< orphan*/  IJK_GLES2_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_GLES2_Renderer_free (int /*<<< orphan*/ *) ; 

void IJK_GLES2_Renderer_freeP(IJK_GLES2_Renderer **renderer)
{
    if (!renderer || !*renderer)
        return;

    IJK_GLES2_Renderer_free(*renderer);
    *renderer = NULL;
}