#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int format; } ;
struct TYPE_13__ {int format; } ;
typedef  TYPE_1__ SDL_VoutOverlay ;
typedef  TYPE_2__ IJK_GLES2_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,char*,int) ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_RENDERER ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int /*<<< orphan*/  GL_VERSION ; 
 TYPE_2__* IJK_GLES2_Renderer_create_rgb565 () ; 
 TYPE_2__* IJK_GLES2_Renderer_create_rgb888 () ; 
 TYPE_2__* IJK_GLES2_Renderer_create_rgbx8888 () ; 
 TYPE_2__* IJK_GLES2_Renderer_create_yuv420p () ; 
 TYPE_2__* IJK_GLES2_Renderer_create_yuv420sp () ; 
 TYPE_2__* IJK_GLES2_Renderer_create_yuv420sp_vtb (TYPE_1__*) ; 
 TYPE_2__* IJK_GLES2_Renderer_create_yuv444p10le () ; 
 int /*<<< orphan*/  IJK_GLES2_printString (char*,int /*<<< orphan*/ ) ; 
#define  SDL_FCC_I420 135 
#define  SDL_FCC_I444P10LE 134 
#define  SDL_FCC_NV12 133 
#define  SDL_FCC_RV16 132 
#define  SDL_FCC_RV24 131 
#define  SDL_FCC_RV32 130 
#define  SDL_FCC_YV12 129 
#define  SDL_FCC__VTB 128 

IJK_GLES2_Renderer *IJK_GLES2_Renderer_create(SDL_VoutOverlay *overlay)
{
    if (!overlay)
        return NULL;

    IJK_GLES2_printString("Version", GL_VERSION);
    IJK_GLES2_printString("Vendor", GL_VENDOR);
    IJK_GLES2_printString("Renderer", GL_RENDERER);
    IJK_GLES2_printString("Extensions", GL_EXTENSIONS);

    IJK_GLES2_Renderer *renderer = NULL;
    switch (overlay->format) {
        case SDL_FCC_RV16:      renderer = IJK_GLES2_Renderer_create_rgb565(); break;
        case SDL_FCC_RV24:      renderer = IJK_GLES2_Renderer_create_rgb888(); break;
        case SDL_FCC_RV32:      renderer = IJK_GLES2_Renderer_create_rgbx8888(); break;
#ifdef __APPLE__
        case SDL_FCC_NV12:      renderer = IJK_GLES2_Renderer_create_yuv420sp(); break;
        case SDL_FCC__VTB:      renderer = IJK_GLES2_Renderer_create_yuv420sp_vtb(overlay); break;
#endif
        case SDL_FCC_YV12:      renderer = IJK_GLES2_Renderer_create_yuv420p(); break;
        case SDL_FCC_I420:      renderer = IJK_GLES2_Renderer_create_yuv420p(); break;
        case SDL_FCC_I444P10LE: renderer = IJK_GLES2_Renderer_create_yuv444p10le(); break;
        default:
            ALOGE("[GLES2] unknown format %4s(%d)\n", (char *)&overlay->format, overlay->format);
            return NULL;
    }

    renderer->format = overlay->format;
    return renderer;
}