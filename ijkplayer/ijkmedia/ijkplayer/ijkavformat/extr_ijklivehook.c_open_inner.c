#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  value; } ;
struct TYPE_14__ {int probesize; int format_probesize; int max_analyze_duration; int fps_probe_size; int max_ts_probe; int nb_streams; int /*<<< orphan*/ * streams; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/ * metadata; TYPE_2__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  url; } ;
struct TYPE_13__ {TYPE_3__* inner; TYPE_1__ io_control; scalar_t__ open_opts; } ;
typedef  TYPE_2__ Context ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_MATCH_CASE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_alloc_context () ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_3__**) ; 
 int avformat_find_stream_info (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int copy_stream_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int open_inner(AVFormatContext *avf)
{
    Context         *c          = avf->priv_data;
    AVDictionary    *tmp_opts   = NULL;
    AVFormatContext *new_avf    = NULL;
    int ret = -1;
    int i   = 0;
    AVDictionaryEntry *t = NULL;
    int fps_flag = 0;

    new_avf = avformat_alloc_context();
    if (!new_avf) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    if (c->open_opts)
        av_dict_copy(&tmp_opts, c->open_opts, 0);

    av_dict_set_int(&tmp_opts, "probesize",         avf->probesize, 0);
    av_dict_set_int(&tmp_opts, "formatprobesize",   avf->format_probesize, 0);
    av_dict_set_int(&tmp_opts, "analyzeduration",   avf->max_analyze_duration, 0);
    av_dict_set_int(&tmp_opts, "fpsprobesize",      avf->fps_probe_size, 0);
    av_dict_set_int(&tmp_opts, "max_ts_probe",      avf->max_ts_probe, 0);

    t = av_dict_get(tmp_opts, "skip-calc-frame-rate", NULL, AV_DICT_MATCH_CASE);
    if (t) {
        fps_flag = (int) strtol(t->value, NULL, 10);
        if (fps_flag > 0) {
            av_dict_set_int(&new_avf->metadata, "skip-calc-frame-rate", fps_flag, 0);
        }
    }

    new_avf->interrupt_callback = avf->interrupt_callback;
    ret = avformat_open_input(&new_avf, c->io_control.url, NULL, &tmp_opts);
    if (ret < 0)
        goto fail;

    ret = avformat_find_stream_info(new_avf, NULL);
    if (ret < 0)
        goto fail;

    for (i = 0; i < new_avf->nb_streams; i++) {
        AVStream *st = avformat_new_stream(avf, NULL);
        if (!st) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        ret = copy_stream_props(st, new_avf->streams[i]);
        if (ret < 0)
            goto fail;
    }

    avformat_close_input(&c->inner);
    c->inner = new_avf;
    new_avf = NULL;
    ret = 0;
fail:
    av_dict_free(&tmp_opts);
    avformat_close_input(&new_avf);
    return ret;
}