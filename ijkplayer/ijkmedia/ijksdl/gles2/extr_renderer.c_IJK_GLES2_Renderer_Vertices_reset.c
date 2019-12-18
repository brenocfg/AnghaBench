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
struct TYPE_3__ {float* vertices; } ;
typedef  TYPE_1__ IJK_GLES2_Renderer ;

/* Variables and functions */

__attribute__((used)) static void IJK_GLES2_Renderer_Vertices_reset(IJK_GLES2_Renderer *renderer)
{
    renderer->vertices[0] = -1.0f;
    renderer->vertices[1] = -1.0f;
    renderer->vertices[2] =  1.0f;
    renderer->vertices[3] = -1.0f;
    renderer->vertices[4] = -1.0f;
    renderer->vertices[5] =  1.0f;
    renderer->vertices[6] =  1.0f;
    renderer->vertices[7] =  1.0f;
}