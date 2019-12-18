#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGD (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  av_lockmgr_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_register_all () ; 
 int /*<<< orphan*/  avcodec_register_all () ; 
 int /*<<< orphan*/  avdevice_register_all () ; 
 int /*<<< orphan*/  avfilter_register_all () ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int /*<<< orphan*/  ffp_log_callback_brief ; 
 TYPE_1__ flush_pkt ; 
 int g_ffmpeg_global_inited ; 
 int /*<<< orphan*/  ijkav_register_all () ; 
 int /*<<< orphan*/  ijkmp_version () ; 
 int /*<<< orphan*/  lockmgr ; 

void ffp_global_init()
{
    if (g_ffmpeg_global_inited)
        return;

    ALOGD("ijkmediaplayer version : %s", ijkmp_version());
    /* register all codecs, demux and protocols */
    avcodec_register_all();
#if CONFIG_AVDEVICE
    avdevice_register_all();
#endif
#if CONFIG_AVFILTER
    avfilter_register_all();
#endif
    av_register_all();

    ijkav_register_all();

    avformat_network_init();

    av_lockmgr_register(lockmgr);
    av_log_set_callback(ffp_log_callback_brief);

    av_init_packet(&flush_pkt);
    flush_pkt.data = (uint8_t *)&flush_pkt;

    g_ffmpeg_global_inited = true;
}