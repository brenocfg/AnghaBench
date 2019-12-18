#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  serial; } ;
struct TYPE_17__ {int /*<<< orphan*/  serial; } ;
struct TYPE_14__ {int audio_clock_serial; int audio_volume; int pause_req; int initialized_decoder; int abort_request; void* video_refresh_tid; void* continue_read_thread; TYPE_6__ videoq; int /*<<< orphan*/  viddec; void* read_tid; int /*<<< orphan*/  _read_tid; int /*<<< orphan*/  _video_refresh_tid; void* accurate_seek_mutex; void* play_mutex; int /*<<< orphan*/  av_sync_type; scalar_t__ muted; TYPE_7__ extclk; TYPE_6__ audioq; TYPE_7__ audclk; TYPE_7__ vidclk; void* audio_accurate_seek_cond; void* video_accurate_seek_cond; TYPE_6__ subtitleq; int /*<<< orphan*/  sampq; int /*<<< orphan*/  subpq; int /*<<< orphan*/  pictq; int /*<<< orphan*/  handle; scalar_t__ xleft; scalar_t__ ytop; int /*<<< orphan*/ * iformat; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_15__ {int startup_volume; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  node_vdec; scalar_t__ mediacodec_mpeg2; scalar_t__ mediacodec_hevc; scalar_t__ mediacodec_avc; scalar_t__ mediacodec_all_videos; scalar_t__ mediacodec_default_name; scalar_t__ video_mime_type; int /*<<< orphan*/  video_disable; scalar_t__ async_init_decoder; TYPE_1__* is; int /*<<< orphan*/  start_on_prepared; int /*<<< orphan*/  av_sync_type; scalar_t__ enable_accurate_seek; int /*<<< orphan*/  pictq_size; scalar_t__ soundtouch_enable; } ;
typedef  TYPE_2__ FFPlayer ;
typedef  int /*<<< orphan*/  AVInputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  SAMPLE_QUEUE_SIZE ; 
 void* SDL_CreateCond () ; 
 void* SDL_CreateMutex () ; 
 void* SDL_CreateThreadEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int SDL_GetError () ; 
 int SDL_MIX_MAXVOLUME ; 
 int /*<<< orphan*/  SDL_WaitThread (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUBPICTURE_QUEUE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 
 int /*<<< orphan*/  decoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,void*) ; 
 int /*<<< orphan*/  ffpipeline_init_video_decoder (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ frame_queue_init (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ijk_soundtouch_create () ; 
 int /*<<< orphan*/  init_clock (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ packet_queue_init (TYPE_6__*) ; 
 int /*<<< orphan*/  read_thread ; 
 int /*<<< orphan*/  stream_close (TYPE_2__*) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  video_refresh_thread ; 

__attribute__((used)) static VideoState *stream_open(FFPlayer *ffp, const char *filename, AVInputFormat *iformat)
{
    assert(!ffp->is);
    VideoState *is;

    is = av_mallocz(sizeof(VideoState));
    if (!is)
        return NULL;
    is->filename = av_strdup(filename);
    if (!is->filename)
        goto fail;
    is->iformat = iformat;
    is->ytop    = 0;
    is->xleft   = 0;
#if defined(__ANDROID__)
    if (ffp->soundtouch_enable) {
        is->handle = ijk_soundtouch_create();
    }
#endif

    /* start video display */
    if (frame_queue_init(&is->pictq, &is->videoq, ffp->pictq_size, 1) < 0)
        goto fail;
    if (frame_queue_init(&is->subpq, &is->subtitleq, SUBPICTURE_QUEUE_SIZE, 0) < 0)
        goto fail;
    if (frame_queue_init(&is->sampq, &is->audioq, SAMPLE_QUEUE_SIZE, 1) < 0)
        goto fail;

    if (packet_queue_init(&is->videoq) < 0 ||
        packet_queue_init(&is->audioq) < 0 ||
        packet_queue_init(&is->subtitleq) < 0)
        goto fail;

    if (!(is->continue_read_thread = SDL_CreateCond())) {
        av_log(NULL, AV_LOG_FATAL, "SDL_CreateCond(): %s\n", SDL_GetError());
        goto fail;
    }

    if (!(is->video_accurate_seek_cond = SDL_CreateCond())) {
        av_log(NULL, AV_LOG_FATAL, "SDL_CreateCond(): %s\n", SDL_GetError());
        ffp->enable_accurate_seek = 0;
    }

    if (!(is->audio_accurate_seek_cond = SDL_CreateCond())) {
        av_log(NULL, AV_LOG_FATAL, "SDL_CreateCond(): %s\n", SDL_GetError());
        ffp->enable_accurate_seek = 0;
    }

    init_clock(&is->vidclk, &is->videoq.serial);
    init_clock(&is->audclk, &is->audioq.serial);
    init_clock(&is->extclk, &is->extclk.serial);
    is->audio_clock_serial = -1;
    if (ffp->startup_volume < 0)
        av_log(NULL, AV_LOG_WARNING, "-volume=%d < 0, setting to 0\n", ffp->startup_volume);
    if (ffp->startup_volume > 100)
        av_log(NULL, AV_LOG_WARNING, "-volume=%d > 100, setting to 100\n", ffp->startup_volume);
    ffp->startup_volume = av_clip(ffp->startup_volume, 0, 100);
    ffp->startup_volume = av_clip(SDL_MIX_MAXVOLUME * ffp->startup_volume / 100, 0, SDL_MIX_MAXVOLUME);
    is->audio_volume = ffp->startup_volume;
    is->muted = 0;
    is->av_sync_type = ffp->av_sync_type;

    is->play_mutex = SDL_CreateMutex();
    is->accurate_seek_mutex = SDL_CreateMutex();
    ffp->is = is;
    is->pause_req = !ffp->start_on_prepared;

    is->video_refresh_tid = SDL_CreateThreadEx(&is->_video_refresh_tid, video_refresh_thread, ffp, "ff_vout");
    if (!is->video_refresh_tid) {
        av_freep(&ffp->is);
        return NULL;
    }

    is->initialized_decoder = 0;
    is->read_tid = SDL_CreateThreadEx(&is->_read_tid, read_thread, ffp, "ff_read");
    if (!is->read_tid) {
        av_log(NULL, AV_LOG_FATAL, "SDL_CreateThread(): %s\n", SDL_GetError());
        goto fail;
    }

    if (ffp->async_init_decoder && !ffp->video_disable && ffp->video_mime_type && strlen(ffp->video_mime_type) > 0
                    && ffp->mediacodec_default_name && strlen(ffp->mediacodec_default_name) > 0) {
        if (ffp->mediacodec_all_videos || ffp->mediacodec_avc || ffp->mediacodec_hevc || ffp->mediacodec_mpeg2) {
            decoder_init(&is->viddec, NULL, &is->videoq, is->continue_read_thread);
            ffp->node_vdec = ffpipeline_init_video_decoder(ffp->pipeline, ffp);
        }
    }
    is->initialized_decoder = 1;

    return is;
fail:
    is->initialized_decoder = 1;
    is->abort_request = true;
    if (is->video_refresh_tid)
        SDL_WaitThread(is->video_refresh_tid, NULL);
    stream_close(ffp);
    return NULL;
}