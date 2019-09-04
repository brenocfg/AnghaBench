#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t windex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_3__* queue; } ;
struct TYPE_9__ {TYPE_1__ pictq; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_12__ {scalar_t__* pitches; int /*<<< orphan*/  is_private; } ;
struct TYPE_11__ {int /*<<< orphan*/  vout; int /*<<< orphan*/  overlay_format; TYPE_2__* is; } ;
struct TYPE_10__ {scalar_t__ width; int allocated; int /*<<< orphan*/  height; TYPE_7__* bmp; } ;
typedef  TYPE_3__ Frame ;
typedef  TYPE_4__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_VoutSetOverlayFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* SDL_Vout_CreateOverlay (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_picture (TYPE_3__*) ; 

__attribute__((used)) static void alloc_picture(FFPlayer *ffp, int frame_format)
{
    VideoState *is = ffp->is;
    Frame *vp;
#ifdef FFP_MERGE
    int sdl_format;
#endif

    vp = &is->pictq.queue[is->pictq.windex];

    free_picture(vp);

#ifdef FFP_MERGE
    video_open(is, vp);
#endif

    SDL_VoutSetOverlayFormat(ffp->vout, ffp->overlay_format);
    vp->bmp = SDL_Vout_CreateOverlay(vp->width, vp->height,
                                   frame_format,
                                   ffp->vout);
#ifdef FFP_MERGE
    if (vp->format == AV_PIX_FMT_YUV420P)
        sdl_format = SDL_PIXELFORMAT_YV12;
    else
        sdl_format = SDL_PIXELFORMAT_ARGB8888;

    if (realloc_texture(&vp->bmp, sdl_format, vp->width, vp->height, SDL_BLENDMODE_NONE, 0) < 0) {
#else
    /* RV16, RV32 contains only one plane */
    if (!vp->bmp || (!vp->bmp->is_private && vp->bmp->pitches[0] < vp->width)) {
#endif
        /* SDL allocates a buffer smaller than requested if the video
         * overlay hardware is unable to support the requested size. */
        av_log(NULL, AV_LOG_FATAL,
               "Error: the video system does not support an image\n"
                        "size of %dx%d pixels. Try using -lowres or -vf \"scale=w:h\"\n"
                        "to reduce the image size.\n", vp->width, vp->height );
        free_picture(vp);
    }

    SDL_LockMutex(is->pictq.mutex);
    vp->allocated = 1;
    SDL_CondSignal(is->pictq.cond);
    SDL_UnlockMutex(is->pictq.mutex);
}