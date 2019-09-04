#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_34__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_27__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_36__ {int /*<<< orphan*/  decode_profiler; TYPE_3__* avctx; int /*<<< orphan*/  start_pts_tb; int /*<<< orphan*/  start_pts; } ;
struct TYPE_40__ {double bytes_per_sec; } ;
struct TYPE_39__ {int last_audio_stream; int last_subtitle_stream; int last_video_stream; int audio_hw_buf_size; double audio_diff_threshold; int audio_stream; int video_stream; int queue_attachments_req; int is_video_high_fps; int subtitle_stream; TYPE_16__ subdec; int /*<<< orphan*/  continue_read_thread; int /*<<< orphan*/  subtitleq; TYPE_10__* subtitle_st; TYPE_10__* video_st; TYPE_16__ viddec; int /*<<< orphan*/  videoq; int /*<<< orphan*/  initialized_decoder; TYPE_16__ auddec; TYPE_10__* audio_st; TYPE_4__* ic; int /*<<< orphan*/  audioq; TYPE_34__ audio_tgt; int /*<<< orphan*/  audio_diff_avg_count; int /*<<< orphan*/  audio_diff_avg_coef; int /*<<< orphan*/  audio_buf_index; int /*<<< orphan*/  audio_buf_size; TYPE_34__ audio_src; scalar_t__ eof; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_44__ {double id; } ;
struct TYPE_43__ {double key; } ;
struct TYPE_42__ {int nb_streams; TYPE_10__** streams; TYPE_1__* iformat; } ;
struct TYPE_41__ {int lowres; double codec_id; int codec_type; char* audio_codec_name; char* subtitle_codec_name; char* video_codec_name; int sample_rate; int channels; double max_fps; int /*<<< orphan*/  subtitle; void* skip_loop_filter; void* skip_idct; void* skip_frame; void* node_vdec; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  async_init_decoder; int /*<<< orphan*/  aout; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_opts; int /*<<< orphan*/  flags2; scalar_t__ fast; TYPE_2__* is; } ;
struct TYPE_38__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_37__ {int flags; int /*<<< orphan*/  read_seek; } ;
struct TYPE_35__ {TYPE_27__ r_frame_rate; TYPE_27__ avg_frame_rate; int /*<<< orphan*/  time_base; int /*<<< orphan*/  start_time; int /*<<< orphan*/  discard; int /*<<< orphan*/  codecpar; } ;
typedef  TYPE_3__ FFPlayer ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_7__ AVCodec ;

/* Variables and functions */
 int AUDIO_DIFF_AVG_NB ; 
 int /*<<< orphan*/  AVCODEC_MODULE_NAME ; 
 int /*<<< orphan*/  AVDISCARD_DEFAULT ; 
 int /*<<< orphan*/  AVDISCARD_NONREF ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_NOBINSEARCH ; 
 int AVFMT_NOGENSEARCH ; 
 int AVFMT_NO_BYTE_SEEK ; 
#define  AVMEDIA_TYPE_AUDIO 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_CODEC_FLAG2_FAST ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFMAX (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_AoutPauseAudio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  SDL_ProfilerReset (int /*<<< orphan*/ *,double) ; 
 int audio_open (TYPE_3__*,int /*<<< orphan*/ ,int,int,TYPE_34__*) ; 
 int /*<<< orphan*/  audio_thread ; 
 double av_codec_get_max_lowres (TYPE_7__*) ; 
 int /*<<< orphan*/  av_codec_set_lowres (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_codec_set_pkt_timebase (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 double av_q2d (TYPE_27__) ; 
 TYPE_3__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 TYPE_7__* avcodec_find_decoder (double) ; 
 TYPE_7__* avcodec_find_decoder_by_name (char const*) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_3__**) ; 
 int /*<<< orphan*/  avcodec_get_name (double) ; 
 int avcodec_open2 (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ **) ; 
 int avcodec_parameters_to_context (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decoder_init (TYPE_16__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int decoder_start (TYPE_16__*,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  exp (int) ; 
 int /*<<< orphan*/  ffp_set_audio_codec_info (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffp_set_subtitle_codec_info (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffpipeline_config_video_decoder (int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* ffpipeline_open_video_decoder (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * filter_codec_opts (int /*<<< orphan*/ ,double,TYPE_4__*,TYPE_10__*,TYPE_7__*) ; 
 int log (double) ; 
 int /*<<< orphan*/  subtitle_thread ; 
 int /*<<< orphan*/  video_thread ; 

__attribute__((used)) static int stream_component_open(FFPlayer *ffp, int stream_index)
{
    VideoState *is = ffp->is;
    AVFormatContext *ic = is->ic;
    AVCodecContext *avctx;
    AVCodec *codec = NULL;
    const char *forced_codec_name = NULL;
    AVDictionary *opts = NULL;
    AVDictionaryEntry *t = NULL;
    int sample_rate, nb_channels;
    int64_t channel_layout;
    int ret = 0;
    int stream_lowres = ffp->lowres;

    if (stream_index < 0 || stream_index >= ic->nb_streams)
        return -1;
    avctx = avcodec_alloc_context3(NULL);
    if (!avctx)
        return AVERROR(ENOMEM);

    ret = avcodec_parameters_to_context(avctx, ic->streams[stream_index]->codecpar);
    if (ret < 0)
        goto fail;
    av_codec_set_pkt_timebase(avctx, ic->streams[stream_index]->time_base);

    codec = avcodec_find_decoder(avctx->codec_id);

    switch (avctx->codec_type) {
        case AVMEDIA_TYPE_AUDIO   : is->last_audio_stream    = stream_index; forced_codec_name = ffp->audio_codec_name; break;
        case AVMEDIA_TYPE_SUBTITLE: is->last_subtitle_stream = stream_index; forced_codec_name = ffp->subtitle_codec_name; break;
        case AVMEDIA_TYPE_VIDEO   : is->last_video_stream    = stream_index; forced_codec_name = ffp->video_codec_name; break;
        default: break;
    }
    if (forced_codec_name)
        codec = avcodec_find_decoder_by_name(forced_codec_name);
    if (!codec) {
        if (forced_codec_name) av_log(NULL, AV_LOG_WARNING,
                                      "No codec could be found with name '%s'\n", forced_codec_name);
        else                   av_log(NULL, AV_LOG_WARNING,
                                      "No codec could be found with id %d\n", avctx->codec_id);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    avctx->codec_id = codec->id;
    if(stream_lowres > av_codec_get_max_lowres(codec)){
        av_log(avctx, AV_LOG_WARNING, "The maximum value for lowres supported by the decoder is %d\n",
                av_codec_get_max_lowres(codec));
        stream_lowres = av_codec_get_max_lowres(codec);
    }
    av_codec_set_lowres(avctx, stream_lowres);

#if FF_API_EMU_EDGE
    if(stream_lowres) avctx->flags |= CODEC_FLAG_EMU_EDGE;
#endif
    if (ffp->fast)
        avctx->flags2 |= AV_CODEC_FLAG2_FAST;
#if FF_API_EMU_EDGE
    if(codec->capabilities & AV_CODEC_CAP_DR1)
        avctx->flags |= CODEC_FLAG_EMU_EDGE;
#endif

    opts = filter_codec_opts(ffp->codec_opts, avctx->codec_id, ic, ic->streams[stream_index], codec);
    if (!av_dict_get(opts, "threads", NULL, 0))
        av_dict_set(&opts, "threads", "auto", 0);
    if (stream_lowres)
        av_dict_set_int(&opts, "lowres", stream_lowres, 0);
    if (avctx->codec_type == AVMEDIA_TYPE_VIDEO || avctx->codec_type == AVMEDIA_TYPE_AUDIO)
        av_dict_set(&opts, "refcounted_frames", "1", 0);
    if ((ret = avcodec_open2(avctx, codec, &opts)) < 0) {
        goto fail;
    }
    if ((t = av_dict_get(opts, "", NULL, AV_DICT_IGNORE_SUFFIX))) {
        av_log(NULL, AV_LOG_ERROR, "Option %s not found.\n", t->key);
#ifdef FFP_MERGE
        ret =  AVERROR_OPTION_NOT_FOUND;
        goto fail;
#endif
    }

    is->eof = 0;
    ic->streams[stream_index]->discard = AVDISCARD_DEFAULT;
    switch (avctx->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
#if CONFIG_AVFILTER
        {
            AVFilterContext *sink;

            is->audio_filter_src.freq           = avctx->sample_rate;
            is->audio_filter_src.channels       = avctx->channels;
            is->audio_filter_src.channel_layout = get_valid_channel_layout(avctx->channel_layout, avctx->channels);
            is->audio_filter_src.fmt            = avctx->sample_fmt;
            SDL_LockMutex(ffp->af_mutex);
            if ((ret = configure_audio_filters(ffp, ffp->afilters, 0)) < 0) {
                SDL_UnlockMutex(ffp->af_mutex);
                goto fail;
            }
            ffp->af_changed = 0;
            SDL_UnlockMutex(ffp->af_mutex);
            sink = is->out_audio_filter;
            sample_rate    = av_buffersink_get_sample_rate(sink);
            nb_channels    = av_buffersink_get_channels(sink);
            channel_layout = av_buffersink_get_channel_layout(sink);
        }
#else
        sample_rate    = avctx->sample_rate;
        nb_channels    = avctx->channels;
        channel_layout = avctx->channel_layout;
#endif

        /* prepare audio output */
        if ((ret = audio_open(ffp, channel_layout, nb_channels, sample_rate, &is->audio_tgt)) < 0)
            goto fail;
        ffp_set_audio_codec_info(ffp, AVCODEC_MODULE_NAME, avcodec_get_name(avctx->codec_id));
        is->audio_hw_buf_size = ret;
        is->audio_src = is->audio_tgt;
        is->audio_buf_size  = 0;
        is->audio_buf_index = 0;

        /* init averaging filter */
        is->audio_diff_avg_coef  = exp(log(0.01) / AUDIO_DIFF_AVG_NB);
        is->audio_diff_avg_count = 0;
        /* since we do not have a precise anough audio FIFO fullness,
           we correct audio sync only if larger than this threshold */
        is->audio_diff_threshold = 2.0 * is->audio_hw_buf_size / is->audio_tgt.bytes_per_sec;

        is->audio_stream = stream_index;
        is->audio_st = ic->streams[stream_index];

        decoder_init(&is->auddec, avctx, &is->audioq, is->continue_read_thread);
        if ((is->ic->iformat->flags & (AVFMT_NOBINSEARCH | AVFMT_NOGENSEARCH | AVFMT_NO_BYTE_SEEK)) && !is->ic->iformat->read_seek) {
            is->auddec.start_pts = is->audio_st->start_time;
            is->auddec.start_pts_tb = is->audio_st->time_base;
        }
        if ((ret = decoder_start(&is->auddec, audio_thread, ffp, "ff_audio_dec")) < 0)
            goto out;
        SDL_AoutPauseAudio(ffp->aout, 0);
        break;
    case AVMEDIA_TYPE_VIDEO:
        is->video_stream = stream_index;
        is->video_st = ic->streams[stream_index];

        if (ffp->async_init_decoder) {
            while (!is->initialized_decoder) {
                SDL_Delay(5);
            }
            if (ffp->node_vdec) {
                is->viddec.avctx = avctx;
                ret = ffpipeline_config_video_decoder(ffp->pipeline, ffp);
            }
            if (ret || !ffp->node_vdec) {
                decoder_init(&is->viddec, avctx, &is->videoq, is->continue_read_thread);
                ffp->node_vdec = ffpipeline_open_video_decoder(ffp->pipeline, ffp);
                if (!ffp->node_vdec)
                    goto fail;
            }
        } else {
            decoder_init(&is->viddec, avctx, &is->videoq, is->continue_read_thread);
            ffp->node_vdec = ffpipeline_open_video_decoder(ffp->pipeline, ffp);
            if (!ffp->node_vdec)
                goto fail;
        }
        if ((ret = decoder_start(&is->viddec, video_thread, ffp, "ff_video_dec")) < 0)
            goto out;

        is->queue_attachments_req = 1;

        if (ffp->max_fps >= 0) {
            if(is->video_st->avg_frame_rate.den && is->video_st->avg_frame_rate.num) {
                double fps = av_q2d(is->video_st->avg_frame_rate);
                SDL_ProfilerReset(&is->viddec.decode_profiler, fps + 0.5);
                if (fps > ffp->max_fps && fps < 130.0) {
                    is->is_video_high_fps = 1;
                    av_log(ffp, AV_LOG_WARNING, "fps: %lf (too high)\n", fps);
                } else {
                    av_log(ffp, AV_LOG_WARNING, "fps: %lf (normal)\n", fps);
                }
            }
            if(is->video_st->r_frame_rate.den && is->video_st->r_frame_rate.num) {
                double tbr = av_q2d(is->video_st->r_frame_rate);
                if (tbr > ffp->max_fps && tbr < 130.0) {
                    is->is_video_high_fps = 1;
                    av_log(ffp, AV_LOG_WARNING, "fps: %lf (too high)\n", tbr);
                } else {
                    av_log(ffp, AV_LOG_WARNING, "fps: %lf (normal)\n", tbr);
                }
            }
        }

        if (is->is_video_high_fps) {
            avctx->skip_frame       = FFMAX(avctx->skip_frame, AVDISCARD_NONREF);
            avctx->skip_loop_filter = FFMAX(avctx->skip_loop_filter, AVDISCARD_NONREF);
            avctx->skip_idct        = FFMAX(avctx->skip_loop_filter, AVDISCARD_NONREF);
        }

        break;
    case AVMEDIA_TYPE_SUBTITLE:
        if (!ffp->subtitle) break;

        is->subtitle_stream = stream_index;
        is->subtitle_st = ic->streams[stream_index];

        ffp_set_subtitle_codec_info(ffp, AVCODEC_MODULE_NAME, avcodec_get_name(avctx->codec_id));

        decoder_init(&is->subdec, avctx, &is->subtitleq, is->continue_read_thread);
        if ((ret = decoder_start(&is->subdec, subtitle_thread, ffp, "ff_subtitle_dec")) < 0)
            goto out;
        break;
    default:
        break;
    }
    goto out;

fail:
    avcodec_free_context(&avctx);
out:
    av_dict_free(&opts);

    return ret;
}