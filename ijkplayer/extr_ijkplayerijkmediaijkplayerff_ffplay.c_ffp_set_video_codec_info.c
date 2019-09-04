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
struct TYPE_4__ {int /*<<< orphan*/  video_codec_info; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_asprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void ffp_set_video_codec_info(FFPlayer *ffp, const char *module, const char *codec)
{
    av_freep(&ffp->video_codec_info);
    ffp->video_codec_info = av_asprintf("%s, %s", module ? module : "", codec ? codec : "");
    av_log(ffp, AV_LOG_INFO, "VideoCodec: %s\n", ffp->video_codec_info);
}