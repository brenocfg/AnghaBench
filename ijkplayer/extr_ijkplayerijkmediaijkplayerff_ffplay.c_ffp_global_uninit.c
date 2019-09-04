#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  av_lockmgr_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_network_deinit () ; 
 int g_ffmpeg_global_inited ; 

void ffp_global_uninit()
{
    if (!g_ffmpeg_global_inited)
        return;

    av_lockmgr_register(NULL);

    // FFP_MERGE: uninit_opts

    avformat_network_deinit();

    g_ffmpeg_global_inited = false;
}