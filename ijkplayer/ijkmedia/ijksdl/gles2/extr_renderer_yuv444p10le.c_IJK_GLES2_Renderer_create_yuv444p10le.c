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
struct TYPE_5__ {int /*<<< orphan*/  func_uploadTexture; int /*<<< orphan*/  func_getBufferWidth; int /*<<< orphan*/  func_use; int /*<<< orphan*/  program; void* um3_color_conversion; void** us2_sampler; } ;
typedef  TYPE_1__ IJK_GLES2_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGI (char*) ; 
 TYPE_1__* IJK_GLES2_Renderer_create_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IJK_GLES2_Renderer_free (TYPE_1__*) ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
 int /*<<< orphan*/  IJK_GLES2_getFragmentShader_yuv444p10le () ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yuv444p10le_getBufferWidth ; 
 int /*<<< orphan*/  yuv444p10le_uploadTexture ; 
 int /*<<< orphan*/  yuv444p10le_use ; 

IJK_GLES2_Renderer *IJK_GLES2_Renderer_create_yuv444p10le()
{
    ALOGI("create render yuv444p10le\n");
    IJK_GLES2_Renderer *renderer = IJK_GLES2_Renderer_create_base(IJK_GLES2_getFragmentShader_yuv444p10le());
    if (!renderer)
        goto fail;

    renderer->us2_sampler[0] = glGetUniformLocation(renderer->program, "us2_SamplerX"); IJK_GLES2_checkError_TRACE("glGetUniformLocation(us2_SamplerX)");
    renderer->us2_sampler[1] = glGetUniformLocation(renderer->program, "us2_SamplerY"); IJK_GLES2_checkError_TRACE("glGetUniformLocation(us2_SamplerY)");
    renderer->us2_sampler[2] = glGetUniformLocation(renderer->program, "us2_SamplerZ"); IJK_GLES2_checkError_TRACE("glGetUniformLocation(us2_SamplerZ)");

    renderer->um3_color_conversion = glGetUniformLocation(renderer->program, "um3_ColorConversion"); IJK_GLES2_checkError_TRACE("glGetUniformLocation(um3_ColorConversionMatrix)");

    renderer->func_use            = yuv444p10le_use;
    renderer->func_getBufferWidth = yuv444p10le_getBufferWidth;
    renderer->func_uploadTexture  = yuv444p10le_uploadTexture;

    return renderer;
fail:
    IJK_GLES2_Renderer_free(renderer);
    return NULL;
}