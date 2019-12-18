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
struct TYPE_8__ {scalar_t__ extradata_size; scalar_t__ extradata; scalar_t__ codec_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  time_base; int /*<<< orphan*/  avg_frame_rate; int /*<<< orphan*/  r_frame_rate; TYPE_2__* codecpar; } ;
typedef  TYPE_1__ AVStream ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int avcodec_parameters_copy (TYPE_2__*,TYPE_2__*) ; 
 int ff_alloc_extradata (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int copy_stream_props(AVStream *st, AVStream *source_st)
{
    int ret;

    if (st->codecpar->codec_id || !source_st->codecpar->codec_id) {
        if (st->codecpar->extradata_size < source_st->codecpar->extradata_size) {
            if (st->codecpar->extradata) {
                av_freep(&st->codecpar->extradata);
                st->codecpar->extradata_size = 0;
            }
            ret = ff_alloc_extradata(st->codecpar,
                                     source_st->codecpar->extradata_size);
            if (ret < 0)
                return ret;
        }
        memcpy(st->codecpar->extradata, source_st->codecpar->extradata,
               source_st->codecpar->extradata_size);
        return 0;
    }
    if ((ret = avcodec_parameters_copy(st->codecpar, source_st->codecpar)) < 0)
        return ret;
    st->r_frame_rate        = source_st->r_frame_rate;
    st->avg_frame_rate      = source_st->avg_frame_rate;
    st->time_base           = source_st->time_base;
    st->sample_aspect_ratio = source_st->sample_aspect_ratio;

    av_dict_copy(&st->metadata, source_st->metadata, 0);
    return 0;
}