#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  func_uploadTexture; int /*<<< orphan*/  func_getBufferWidth; int /*<<< orphan*/  func_use; int /*<<< orphan*/  program; int /*<<< orphan*/ * us2_sampler; } ;
typedef  TYPE_1__ IJK_GLES2_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGI (char*) ; 
 TYPE_1__* IJK_GLES2_Renderer_create_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IJK_GLES2_Renderer_free (TYPE_1__*) ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
 int /*<<< orphan*/  IJK_GLES2_getFragmentShader_rgb () ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rgb565_getBufferWidth ; 
 int /*<<< orphan*/  rgb565_uploadTexture ; 
 int /*<<< orphan*/  rgb_use ; 

IJK_GLES2_Renderer *IJK_GLES2_Renderer_create_rgb565()
{
    ALOGI("create render rgb565\n");
    IJK_GLES2_Renderer *renderer = IJK_GLES2_Renderer_create_base(IJK_GLES2_getFragmentShader_rgb());
    if (!renderer)
        goto fail;

    renderer->us2_sampler[0] = glGetUniformLocation(renderer->program, "us2_SamplerX"); IJK_GLES2_checkError_TRACE("glGetUniformLocation(us2_SamplerX)");

    renderer->func_use            = rgb_use;
    renderer->func_getBufferWidth = rgb565_getBufferWidth;
    renderer->func_uploadTexture  = rgb565_uploadTexture;

    return renderer;
fail:
    IJK_GLES2_Renderer_free(renderer);
    return NULL;
}