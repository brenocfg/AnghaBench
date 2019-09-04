#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int video_stream; int audio_stream; int subtitle_stream; TYPE_4__* ic; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_14__ {int codec_type; } ;
struct TYPE_13__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_12__ {TYPE_2__* is; } ;
struct TYPE_10__ {TYPE_5__* codecpar; } ;
typedef  TYPE_3__ FFPlayer ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stream_component_close (TYPE_3__*,int) ; 
 int stream_component_open (TYPE_3__*,int) ; 

int ffp_set_stream_selected(FFPlayer *ffp, int stream, int selected)
{
    VideoState        *is = ffp->is;
    AVFormatContext   *ic = NULL;
    AVCodecParameters *codecpar = NULL;
    if (!is)
        return -1;
    ic = is->ic;
    if (!ic)
        return -1;

    if (stream < 0 || stream >= ic->nb_streams) {
        av_log(ffp, AV_LOG_ERROR, "invalid stream index %d >= stream number (%d)\n", stream, ic->nb_streams);
        return -1;
    }

    codecpar = ic->streams[stream]->codecpar;

    if (selected) {
        switch (codecpar->codec_type) {
            case AVMEDIA_TYPE_VIDEO:
                if (stream != is->video_stream && is->video_stream >= 0)
                    stream_component_close(ffp, is->video_stream);
                break;
            case AVMEDIA_TYPE_AUDIO:
                if (stream != is->audio_stream && is->audio_stream >= 0)
                    stream_component_close(ffp, is->audio_stream);
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                if (stream != is->subtitle_stream && is->subtitle_stream >= 0)
                    stream_component_close(ffp, is->subtitle_stream);
                break;
            default:
                av_log(ffp, AV_LOG_ERROR, "select invalid stream %d of video type %d\n", stream, codecpar->codec_type);
                return -1;
        }
        return stream_component_open(ffp, stream);
    } else {
        switch (codecpar->codec_type) {
            case AVMEDIA_TYPE_VIDEO:
                if (stream == is->video_stream)
                    stream_component_close(ffp, is->video_stream);
                break;
            case AVMEDIA_TYPE_AUDIO:
                if (stream == is->audio_stream)
                    stream_component_close(ffp, is->audio_stream);
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                if (stream == is->subtitle_stream)
                    stream_component_close(ffp, is->subtitle_stream);
                break;
            default:
                av_log(ffp, AV_LOG_ERROR, "select invalid stream %d of audio type %d\n", stream, codecpar->codec_type);
                return -1;
        }
        return 0;
    }
}