#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {int alpha_mask_fg_set; } ;
struct TYPE_6__ {int group_count; int /*<<< orphan*/  texture_id; } ;
typedef  TYPE_1__ ImageRenderData ;

/* Variables and functions */
 int /*<<< orphan*/  BLEND_ONTO_OPAQUE ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RED ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GRAPHICS_ALPHA_MASK_PROGRAM ; 
 int /*<<< orphan*/  GRAPHICS_UNIT ; 
 int /*<<< orphan*/  OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_program (int /*<<< orphan*/ ) ; 
 TYPE_5__ cell_uniform_data ; 
 int /*<<< orphan*/  draw_graphics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  foreground ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_data_for_centered_image (TYPE_1__*,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  program_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_graphics_data_to_gpu (int,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
draw_centered_alpha_mask(ssize_t gvao_idx, size_t screen_width, size_t screen_height, size_t width, size_t height, uint8_t *canvas) {
    static ImageRenderData data = {.group_count=1};
    gpu_data_for_centered_image(&data, screen_width, screen_height, width, height);
    if (!data.texture_id) { glGenTextures(1, &data.texture_id); }
    glBindTexture(GL_TEXTURE_2D, data.texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, canvas);
    bind_program(GRAPHICS_ALPHA_MASK_PROGRAM);
    if (!cell_uniform_data.alpha_mask_fg_set) {
        cell_uniform_data.alpha_mask_fg_set = true;
        glUniform1i(glGetUniformLocation(program_id(GRAPHICS_ALPHA_MASK_PROGRAM), "image"), GRAPHICS_UNIT);
        glUniform1ui(glGetUniformLocation(program_id(GRAPHICS_ALPHA_MASK_PROGRAM), "fg"), OPT(foreground));
    }
    glScissor(0, 0, screen_width, screen_height);
    send_graphics_data_to_gpu(1, gvao_idx, &data);
    glEnable(GL_BLEND);
    BLEND_ONTO_OPAQUE;
    draw_graphics(GRAPHICS_ALPHA_MASK_PROGRAM, 0, gvao_idx, &data, 0, 1);
    glDisable(GL_BLEND);
}