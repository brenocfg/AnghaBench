#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_8__ {int format; int width; int height; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_2__* linked_frame; TYPE_2__* managed_frame; } ;
typedef  TYPE_1__ SDL_VoutOverlay_Opaque ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_image_fill_arrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static AVFrame *opaque_setup_frame(SDL_VoutOverlay_Opaque* opaque, enum AVPixelFormat format, int width, int height)
{
    AVFrame *managed_frame = av_frame_alloc();
    if (!managed_frame) {
        return NULL;
    }

    AVFrame *linked_frame = av_frame_alloc();
    if (!linked_frame) {
        av_frame_free(&managed_frame);
        return NULL;
    }

    /*-
     * Lazily allocate frame buffer in opaque_obtain_managed_frame_buffer
     *
     * For refererenced frame management, we use buffer allocated by decoder
     *
    int frame_bytes = avpicture_get_size(format, width, height);
    AVBufferRef *frame_buffer_ref = av_buffer_alloc(frame_bytes);
    if (!frame_buffer_ref)
        return NULL;
    opaque->frame_buffer  = frame_buffer_ref;
     */

    managed_frame->format = format;
    managed_frame->width  = width;
    managed_frame->height = height;
    av_image_fill_arrays(managed_frame->data, managed_frame->linesize ,NULL,
                         format, width, height, 1);
    opaque->managed_frame = managed_frame;
    opaque->linked_frame  = linked_frame;
    return managed_frame;
}