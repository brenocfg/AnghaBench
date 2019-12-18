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
struct TYPE_6__ {int /*<<< orphan*/ * plane_textures; } ;
struct TYPE_5__ {int* pitches; int h; int format; int /*<<< orphan*/  const** pixels; } ;
typedef  TYPE_1__ SDL_VoutOverlay ;
typedef  TYPE_2__ IJK_GLES2_Renderer ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLsizei ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,int) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_RED_EXT ; 
 int /*<<< orphan*/  GL_RG_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
#define  SDL_FCC__VTB 128 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static GLboolean yuv420sp_uploadTexture(IJK_GLES2_Renderer *renderer, SDL_VoutOverlay *overlay)
{
    if (!renderer || !overlay)
        return GL_FALSE;

    const GLsizei widths[2]    = { overlay->pitches[0], overlay->pitches[1] / 2 };
    const GLsizei heights[2]   = { overlay->h,          overlay->h / 2 };
    const GLubyte *pixels[2]   = { overlay->pixels[0],  overlay->pixels[1] };

    switch (overlay->format) {
        case SDL_FCC__VTB:
            break;
        default:
            ALOGE("[yuv420sp] unexpected format %x\n", overlay->format);
            return GL_FALSE;
    }

    glBindTexture(GL_TEXTURE_2D, renderer->plane_textures[0]);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RED_EXT,
                 widths[0],
                 heights[0],
                 0,
                 GL_RED_EXT,
                 GL_UNSIGNED_BYTE,
                 pixels[0]);

    glBindTexture(GL_TEXTURE_2D, renderer->plane_textures[1]);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RG_EXT,
                 widths[1],
                 heights[1],
                 0,
                 GL_RG_EXT,
                 GL_UNSIGNED_BYTE,
                 pixels[1]);

    return GL_TRUE;
}