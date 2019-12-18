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
struct TYPE_4__ {int seek_by_bytes; int fast; int decoder_reorder_pts; int loop; int infinite_buffer; double rdftspeed; int autorotate; int find_stream_info; int start_on_prepared; int sync_av_start; int packet_buffering; int max_fps; float pf_playback_rate; float pf_playback_volume; int /*<<< orphan*/  dcc; int /*<<< orphan*/  stat; int /*<<< orphan*/ * ijkio_inject_opaque; int /*<<< orphan*/ * inject_opaque; int /*<<< orphan*/  msg_queue; int /*<<< orphan*/  ijkio_manager_ctx; int /*<<< orphan*/  app_ctx; scalar_t__ pf_playback_volume_changed; scalar_t__ pf_playback_rate_changed; scalar_t__ af_changed; scalar_t__ vf_changed; int /*<<< orphan*/  vdps_sampler; int /*<<< orphan*/  vfps_sampler; int /*<<< orphan*/  meta; scalar_t__ render_wait_start; scalar_t__ ijkmeta_delay_init; int /*<<< orphan*/ * mediacodec_default_name; int /*<<< orphan*/ * video_mime_type; scalar_t__ async_init_decoder; scalar_t__ no_time_adjust; int /*<<< orphan*/ * iformat_name; scalar_t__ soundtouch_enable; scalar_t__ opensles; scalar_t__ mediacodec_auto_rotate; scalar_t__ mediacodec_handle_resolution_change; scalar_t__ mediacodec_mpeg2; scalar_t__ mediacodec_hevc; scalar_t__ mediacodec_avc; scalar_t__ mediacodec_all_videos; scalar_t__ vtb_wait_async; scalar_t__ vtb_handle_resolution_change; scalar_t__ vtb_async; scalar_t__ vtb_max_frame_width; scalar_t__ videotoolbox; int /*<<< orphan*/  pictq_size; scalar_t__ playable_duration_ms; int /*<<< orphan*/  accurate_seek_timeout; scalar_t__ enable_accurate_seek; scalar_t__ first_video_frame_rendered; scalar_t__ error_count; scalar_t__ error; scalar_t__ auto_resume; scalar_t__ prepared; scalar_t__ last_error; int /*<<< orphan*/  overlay_format; int /*<<< orphan*/  subtitle_codec_info; int /*<<< orphan*/  audio_codec_info; int /*<<< orphan*/  video_codec_info; scalar_t__ sar_den; scalar_t__ sar_num; int /*<<< orphan*/ * node_vdec; int /*<<< orphan*/ * pipeline; int /*<<< orphan*/ * vout; int /*<<< orphan*/ * aout; scalar_t__ audio_callback_time; int /*<<< orphan*/  sws_flags; int /*<<< orphan*/ * vfilter0; int /*<<< orphan*/ * afilters; scalar_t__ nb_vfilters; int /*<<< orphan*/  vfilters_list; int /*<<< orphan*/  video_codec_name; int /*<<< orphan*/  audio_codec_name; int /*<<< orphan*/  show_mode; scalar_t__ seek_at_start; scalar_t__ framedrop; scalar_t__ autoexit; scalar_t__ lowres; scalar_t__ genpts; void* duration; void* start_time; int /*<<< orphan*/  av_sync_type; scalar_t__ show_status; scalar_t__ display_disable; int /*<<< orphan*/  wanted_stream_spec; scalar_t__ video_disable; scalar_t__ audio_disable; int /*<<< orphan*/  input_filename; int /*<<< orphan*/  swr_preset_opts; int /*<<< orphan*/  swr_opts; int /*<<< orphan*/  player_opts; int /*<<< orphan*/  sws_dict; int /*<<< orphan*/  codec_opts; int /*<<< orphan*/  format_opts; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_SYNC_AUDIO_MASTER ; 
 int /*<<< orphan*/  MAX_ACCURATE_SEEK_TIMEOUT ; 
 int /*<<< orphan*/  SDL_FCC_RV32 ; 
 int /*<<< orphan*/  SDL_SpeedSamplerReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHOW_MODE_NONE ; 
 int /*<<< orphan*/  SWS_FAST_BILINEAR ; 
 int /*<<< orphan*/  VIDEO_PICTURE_QUEUE_SIZE_DEFAULT ; 
 int /*<<< orphan*/  av_application_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_opt_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_reset_demux_cache_control (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffp_reset_statistic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijkio_manager_destroyp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijkmeta_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_queue_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static void ffp_reset_internal(FFPlayer *ffp)
{
    /* ffp->is closed in stream_close() */
    av_opt_free(ffp);

    /* format/codec options */
    av_dict_free(&ffp->format_opts);
    av_dict_free(&ffp->codec_opts);
    av_dict_free(&ffp->sws_dict);
    av_dict_free(&ffp->player_opts);
    av_dict_free(&ffp->swr_opts);
    av_dict_free(&ffp->swr_preset_opts);

    /* ffplay options specified by the user */
    av_freep(&ffp->input_filename);
    ffp->audio_disable          = 0;
    ffp->video_disable          = 0;
    memset(ffp->wanted_stream_spec, 0, sizeof(ffp->wanted_stream_spec));
    ffp->seek_by_bytes          = -1;
    ffp->display_disable        = 0;
    ffp->show_status            = 0;
    ffp->av_sync_type           = AV_SYNC_AUDIO_MASTER;
    ffp->start_time             = AV_NOPTS_VALUE;
    ffp->duration               = AV_NOPTS_VALUE;
    ffp->fast                   = 1;
    ffp->genpts                 = 0;
    ffp->lowres                 = 0;
    ffp->decoder_reorder_pts    = -1;
    ffp->autoexit               = 0;
    ffp->loop                   = 1;
    ffp->framedrop              = 0; // option
    ffp->seek_at_start          = 0;
    ffp->infinite_buffer        = -1;
    ffp->show_mode              = SHOW_MODE_NONE;
    av_freep(&ffp->audio_codec_name);
    av_freep(&ffp->video_codec_name);
    ffp->rdftspeed              = 0.02;
#if CONFIG_AVFILTER
    av_freep(&ffp->vfilters_list);
    ffp->nb_vfilters            = 0;
    ffp->afilters               = NULL;
    ffp->vfilter0               = NULL;
#endif
    ffp->autorotate             = 1;
    ffp->find_stream_info       = 1;

    ffp->sws_flags              = SWS_FAST_BILINEAR;

    /* current context */
    ffp->audio_callback_time    = 0;

    /* extra fields */
    ffp->aout                   = NULL; /* reset outside */
    ffp->vout                   = NULL; /* reset outside */
    ffp->pipeline               = NULL;
    ffp->node_vdec              = NULL;
    ffp->sar_num                = 0;
    ffp->sar_den                = 0;

    av_freep(&ffp->video_codec_info);
    av_freep(&ffp->audio_codec_info);
    av_freep(&ffp->subtitle_codec_info);
    ffp->overlay_format         = SDL_FCC_RV32;

    ffp->last_error             = 0;
    ffp->prepared               = 0;
    ffp->auto_resume            = 0;
    ffp->error                  = 0;
    ffp->error_count            = 0;
    ffp->start_on_prepared      = 1;
    ffp->first_video_frame_rendered = 0;
    ffp->sync_av_start          = 1;
    ffp->enable_accurate_seek   = 0;
    ffp->accurate_seek_timeout  = MAX_ACCURATE_SEEK_TIMEOUT;

    ffp->playable_duration_ms           = 0;

    ffp->packet_buffering               = 1;
    ffp->pictq_size                     = VIDEO_PICTURE_QUEUE_SIZE_DEFAULT; // option
    ffp->max_fps                        = 31; // option

    ffp->videotoolbox                   = 0; // option
    ffp->vtb_max_frame_width            = 0; // option
    ffp->vtb_async                      = 0; // option
    ffp->vtb_handle_resolution_change   = 0; // option
    ffp->vtb_wait_async                 = 0; // option

    ffp->mediacodec_all_videos          = 0; // option
    ffp->mediacodec_avc                 = 0; // option
    ffp->mediacodec_hevc                = 0; // option
    ffp->mediacodec_mpeg2               = 0; // option
    ffp->mediacodec_handle_resolution_change = 0; // option
    ffp->mediacodec_auto_rotate         = 0; // option

    ffp->opensles                       = 0; // option
    ffp->soundtouch_enable              = 0; // option

    ffp->iformat_name                   = NULL; // option

    ffp->no_time_adjust                 = 0; // option
    ffp->async_init_decoder             = 0; // option
    ffp->video_mime_type                = NULL; // option
    ffp->mediacodec_default_name        = NULL; // option
    ffp->ijkmeta_delay_init             = 0; // option
    ffp->render_wait_start              = 0;

    ijkmeta_reset(ffp->meta);

    SDL_SpeedSamplerReset(&ffp->vfps_sampler);
    SDL_SpeedSamplerReset(&ffp->vdps_sampler);

    /* filters */
    ffp->vf_changed                     = 0;
    ffp->af_changed                     = 0;
    ffp->pf_playback_rate               = 1.0f;
    ffp->pf_playback_rate_changed       = 0;
    ffp->pf_playback_volume             = 1.0f;
    ffp->pf_playback_volume_changed     = 0;

    av_application_closep(&ffp->app_ctx);
    ijkio_manager_destroyp(&ffp->ijkio_manager_ctx);

    msg_queue_flush(&ffp->msg_queue);

    ffp->inject_opaque = NULL;
    ffp->ijkio_inject_opaque = NULL;
    ffp_reset_statistic(&ffp->stat);
    ffp_reset_demux_cache_control(&ffp->dcc);
}