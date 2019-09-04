#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int Uint32 ;
struct TYPE_13__ {int overlay_format; } ;
struct TYPE_12__ {int format; int w; int h; int /*<<< orphan*/  func_fill_frame; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  (* free_l ) (TYPE_2__*) ;int /*<<< orphan*/  pixels; int /*<<< orphan*/  pitches; int /*<<< orphan*/ * opaque_class; TYPE_1__* opaque; } ;
struct TYPE_11__ {int planes; int /*<<< orphan*/  managed_frame; int /*<<< orphan*/  pixels; int /*<<< orphan*/  pitches; int /*<<< orphan*/  sws_flags; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ SDL_VoutOverlay_Opaque ;
typedef  TYPE_2__ SDL_VoutOverlay ;
typedef  TYPE_3__ SDL_Vout ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,...) ; 
 int AV_PIX_FMT_0BGR32 ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_RGB24 ; 
 int AV_PIX_FMT_RGB565 ; 
#define  AV_PIX_FMT_YUV420P 137 
#define  AV_PIX_FMT_YUV444P10LE 136 
#define  AV_PIX_FMT_YUVJ420P 135 
 int IJKALIGN (int,int) ; 
 int /*<<< orphan*/  SDLTRACE (char*,int,int,char const*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  SDL_CreateMutex () ; 
#define  SDL_FCC_I420 134 
#define  SDL_FCC_I444P10LE 133 
#define  SDL_FCC_RV16 132 
#define  SDL_FCC_RV24 131 
#define  SDL_FCC_RV32 130 
#define  SDL_FCC_YV12 129 
#define  SDL_FCC__GLES2 128 
 TYPE_2__* SDL_VoutOverlay_CreateInternal (int) ; 
 int /*<<< orphan*/  SWS_BILINEAR ; 
 int /*<<< orphan*/  func_fill_frame ; 
 int /*<<< orphan*/  func_free_l (TYPE_2__*) ; 
 int /*<<< orphan*/  func_lock ; 
 int /*<<< orphan*/  func_unlock ; 
 int /*<<< orphan*/  g_vout_overlay_ffmpeg_class ; 
 int /*<<< orphan*/  opaque_setup_frame (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  overlay_fill (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

SDL_VoutOverlay *SDL_VoutFFmpeg_CreateOverlay(int width, int height, int frame_format, SDL_Vout *display)
{
    Uint32 overlay_format = display->overlay_format;
    switch (overlay_format) {
        case SDL_FCC__GLES2: {
            switch (frame_format) {
                case AV_PIX_FMT_YUV444P10LE:
                    overlay_format = SDL_FCC_I444P10LE;
                    break;
                case AV_PIX_FMT_YUV420P:
                case AV_PIX_FMT_YUVJ420P:
                default:
#if defined(__ANDROID__)
                    overlay_format = SDL_FCC_YV12;
#else
                    overlay_format = SDL_FCC_I420;
#endif
                    break;
            }
            break;
        }
    }

    SDLTRACE("SDL_VoutFFmpeg_CreateOverlay(w=%d, h=%d, fmt=%.4s(0x%x, dp=%p)\n",
        width, height, (const char*) &overlay_format, overlay_format, display);

    SDL_VoutOverlay *overlay = SDL_VoutOverlay_CreateInternal(sizeof(SDL_VoutOverlay_Opaque));
    if (!overlay) {
        ALOGE("overlay allocation failed");
        return NULL;
    }

    SDL_VoutOverlay_Opaque *opaque = overlay->opaque;
    opaque->mutex         = SDL_CreateMutex();
    opaque->sws_flags     = SWS_BILINEAR;

    overlay->opaque_class = &g_vout_overlay_ffmpeg_class;
    overlay->format       = overlay_format;
    overlay->pitches      = opaque->pitches;
    overlay->pixels       = opaque->pixels;
    overlay->w            = width;
    overlay->h            = height;
    overlay->free_l             = func_free_l;
    overlay->lock               = func_lock;
    overlay->unlock             = func_unlock;
    overlay->func_fill_frame    = func_fill_frame;

    enum AVPixelFormat ff_format = AV_PIX_FMT_NONE;
    int buf_width = width;
    int buf_height = height;
    switch (overlay_format) {
    case SDL_FCC_I420:
    case SDL_FCC_YV12: {
        ff_format = AV_PIX_FMT_YUV420P;
        // FIXME: need runtime config
#if defined(__ANDROID__)
        // 16 bytes align pitch for arm-neon image-convert
        buf_width = IJKALIGN(width, 16); // 1 bytes per pixel for Y-plane
#elif defined(__APPLE__)
        // 2^n align for width
        buf_width = width;
        if (width > 0)
            buf_width = 1 << (sizeof(int) * 8 - __builtin_clz(width));
#else
        buf_width = IJKALIGN(width, 16); // unknown platform
#endif
        opaque->planes = 3;
        break;
    }
    case SDL_FCC_I444P10LE: {
        ff_format = AV_PIX_FMT_YUV444P10LE;
        // FIXME: need runtime config
#if defined(__ANDROID__)
        // 16 bytes align pitch for arm-neon image-convert
        buf_width = IJKALIGN(width, 16); // 1 bytes per pixel for Y-plane
#elif defined(__APPLE__)
        // 2^n align for width
        buf_width = width;
        if (width > 0)
            buf_width = 1 << (sizeof(int) * 8 - __builtin_clz(width));
#else
        buf_width = IJKALIGN(width, 16); // unknown platform
#endif
        opaque->planes = 3;
        break;
    }
    case SDL_FCC_RV16: {
        ff_format = AV_PIX_FMT_RGB565;
        buf_width = IJKALIGN(width, 8); // 2 bytes per pixel
        opaque->planes = 1;
        break;
    }
    case SDL_FCC_RV24: {
        ff_format = AV_PIX_FMT_RGB24;
#if defined(__ANDROID__)
        // 16 bytes align pitch for arm-neon image-convert
        buf_width = IJKALIGN(width, 16); // 1 bytes per pixel for Y-plane
#elif defined(__APPLE__)
        buf_width = width;
#else
        buf_width = IJKALIGN(width, 16); // unknown platform
#endif
        opaque->planes = 1;
        break;
    }
    case SDL_FCC_RV32: {
        ff_format = AV_PIX_FMT_0BGR32;
        buf_width = IJKALIGN(width, 4); // 4 bytes per pixel
        opaque->planes = 1;
        break;
    }
    default:
        ALOGE("SDL_VoutFFmpeg_CreateOverlay(...): unknown format %.4s(0x%x)\n", (char*)&overlay_format, overlay_format);
        goto fail;
    }

    opaque->managed_frame = opaque_setup_frame(opaque, ff_format, buf_width, buf_height);
    if (!opaque->managed_frame) {
        ALOGE("overlay->opaque->frame allocation failed\n");
        goto fail;
    }
    overlay_fill(overlay, opaque->managed_frame, opaque->planes);

    return overlay;

fail:
    func_free_l(overlay);
    return NULL;
}