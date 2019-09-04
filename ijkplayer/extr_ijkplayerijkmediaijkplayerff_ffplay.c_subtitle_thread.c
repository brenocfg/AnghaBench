#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* avctx; int /*<<< orphan*/  pkt_serial; } ;
struct TYPE_10__ {int /*<<< orphan*/  subpq; TYPE_7__ subdec; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_14__ {double pts; } ;
struct TYPE_12__ {TYPE_2__* is; } ;
struct TYPE_11__ {double pts; scalar_t__ uploaded; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  serial; TYPE_8__ sub; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ Frame ;
typedef  TYPE_4__ FFPlayer ;

/* Variables and functions */
 double AV_NOPTS_VALUE ; 
 scalar_t__ AV_TIME_BASE ; 
 int decoder_decode_frame (TYPE_4__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_8__*) ; 
 TYPE_3__* frame_queue_peek_writable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_queue_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int subtitle_thread(void *arg)
{
    FFPlayer *ffp = arg;
    VideoState *is = ffp->is;
    Frame *sp;
    int got_subtitle;
    double pts;

    for (;;) {
        if (!(sp = frame_queue_peek_writable(&is->subpq)))
            return 0;

        if ((got_subtitle = decoder_decode_frame(ffp, &is->subdec, NULL, &sp->sub)) < 0)
            break;

        pts = 0;
#ifdef FFP_MERGE
        if (got_subtitle && sp->sub.format == 0) {
#else
        if (got_subtitle) {
#endif
            if (sp->sub.pts != AV_NOPTS_VALUE)
                pts = sp->sub.pts / (double)AV_TIME_BASE;
            sp->pts = pts;
            sp->serial = is->subdec.pkt_serial;
            sp->width = is->subdec.avctx->width;
            sp->height = is->subdec.avctx->height;
            sp->uploaded = 0;

            /* now we can update the picture count */
            frame_queue_push(&is->subpq);
#ifdef FFP_MERGE
        } else if (got_subtitle) {
            avsubtitle_free(&sp->sub);
#endif
        }
    }
    return 0;
}