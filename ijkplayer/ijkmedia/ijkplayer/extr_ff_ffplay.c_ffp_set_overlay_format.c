#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int overlay_format; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  SDL_FCC_I420 134 
#define  SDL_FCC_I444P10LE 133 
#define  SDL_FCC_RV16 132 
#define  SDL_FCC_RV24 131 
#define  SDL_FCC_RV32 130 
#define  SDL_FCC_YV12 129 
#define  SDL_FCC__GLES2 128 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

void ffp_set_overlay_format(FFPlayer *ffp, int chroma_fourcc)
{
    switch (chroma_fourcc) {
        case SDL_FCC__GLES2:
        case SDL_FCC_I420:
        case SDL_FCC_YV12:
        case SDL_FCC_RV16:
        case SDL_FCC_RV24:
        case SDL_FCC_RV32:
            ffp->overlay_format = chroma_fourcc;
            break;
#ifdef __APPLE__
        case SDL_FCC_I444P10LE:
            ffp->overlay_format = chroma_fourcc;
            break;
#endif
        default:
            av_log(ffp, AV_LOG_ERROR, "ffp_set_overlay_format: unknown chroma fourcc: %d\n", chroma_fourcc);
            break;
    }
}