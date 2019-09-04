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
struct TYPE_7__ {int buffering_on; int seek_buffering; scalar_t__ seek_req; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_8__ {TYPE_1__* is; int /*<<< orphan*/  packet_buffering; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  FFP_MSG_BUFFERING_END ; 
 int /*<<< orphan*/  FFP_MSG_BUFFERING_START ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffp_notify_msg2 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stream_update_pause_l (TYPE_2__*) ; 

void ffp_toggle_buffering_l(FFPlayer *ffp, int buffering_on)
{
    if (!ffp->packet_buffering)
        return;

    VideoState *is = ffp->is;
    if (buffering_on && !is->buffering_on) {
        av_log(ffp, AV_LOG_DEBUG, "ffp_toggle_buffering_l: start\n");
        is->buffering_on = 1;
        stream_update_pause_l(ffp);
        if (is->seek_req) {
            is->seek_buffering = 1;
            ffp_notify_msg2(ffp, FFP_MSG_BUFFERING_START, 1);
        } else {
            ffp_notify_msg2(ffp, FFP_MSG_BUFFERING_START, 0);
        }
    } else if (!buffering_on && is->buffering_on){
        av_log(ffp, AV_LOG_DEBUG, "ffp_toggle_buffering_l: end\n");
        is->buffering_on = 0;
        stream_update_pause_l(ffp);
        if (is->seek_buffering) {
            is->seek_buffering = 0;
            ffp_notify_msg2(ffp, FFP_MSG_BUFFERING_END, 1);
        } else {
            ffp_notify_msg2(ffp, FFP_MSG_BUFFERING_END, 0);
        }
    }
}