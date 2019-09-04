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
struct TYPE_3__ {int* pitches; } ;
typedef  TYPE_1__ SDL_VoutOverlay ;
typedef  int /*<<< orphan*/  IJK_GLES2_Renderer ;
typedef  int GLsizei ;

/* Variables and functions */

__attribute__((used)) static GLsizei rgbx8888_getBufferWidth(IJK_GLES2_Renderer *renderer, SDL_VoutOverlay *overlay)
{
    if (!overlay)
        return 0;

    return overlay->pitches[0] / 4;
}