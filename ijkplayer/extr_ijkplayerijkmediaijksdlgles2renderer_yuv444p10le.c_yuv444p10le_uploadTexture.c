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
struct TYPE_5__ {int* pitches; int const h; int format; int /*<<< orphan*/  const** pixels; } ;
typedef  TYPE_1__ SDL_VoutOverlay ;
typedef  TYPE_2__ IJK_GLES2_Renderer ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLsizei ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,int) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_LUMINANCE_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
#define  SDL_FCC_I444P10LE 128 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static GLboolean yuv444p10le_uploadTexture(IJK_GLES2_Renderer *renderer, SDL_VoutOverlay *overlay)
{
    if (!renderer || !overlay)
        return GL_FALSE;

          int     planes[3]    = { 0, 1, 2 };
    const GLsizei widths[3]    = { overlay->pitches[0] / 2, overlay->pitches[1] / 2, overlay->pitches[2] / 2 };
    const GLsizei heights[3]   = { overlay->h,              overlay->h,              overlay->h };
    const GLubyte *pixels[3]   = { overlay->pixels[0],      overlay->pixels[1],      overlay->pixels[2] };

    switch (overlay->format) {
        case SDL_FCC_I444P10LE:
            break;
        default:
            ALOGE("[yuv420p10le] unexpected format %x\n", overlay->format);
            return GL_FALSE;
    }

    for (int i = 0; i < 3; ++i) {
        int plane = planes[i];

        glBindTexture(GL_TEXTURE_2D, renderer->plane_textures[i]);  IJK_GLES2_checkError_TRACE("glBindTexture");

        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_LUMINANCE_ALPHA,
                     widths[plane],
                     heights[plane],
                     0,
                     GL_LUMINANCE_ALPHA,
                     GL_UNSIGNED_BYTE,
                     pixels[plane]);    IJK_GLES2_checkError_TRACE("glTexImage2D");
    }

    return GL_TRUE;
}