#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; int /*<<< orphan*/  duration; } ;
struct TYPE_8__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; int /*<<< orphan*/  duration; } ;
struct TYPE_10__ {int /*<<< orphan*/  logical_file_size; int /*<<< orphan*/  cache_count_bytes; int /*<<< orphan*/  cache_file_pos; int /*<<< orphan*/  cache_file_forwards; int /*<<< orphan*/  cache_physical_pos; int /*<<< orphan*/  byte_count; int /*<<< orphan*/  latest_seek_load_duration; int /*<<< orphan*/  buf_capacity; int /*<<< orphan*/  buf_forwards; int /*<<< orphan*/  buf_backwards; int /*<<< orphan*/  tcp_read_sampler; int /*<<< orphan*/  bit_rate; TYPE_3__ audio_cache; TYPE_2__ video_cache; int /*<<< orphan*/  vdec_type; } ;
struct TYPE_11__ {TYPE_4__ stat; TYPE_1__* is; } ;
struct TYPE_7__ {int /*<<< orphan*/  subtitle_stream; int /*<<< orphan*/  audio_stream; int /*<<< orphan*/  video_stream; } ;
typedef  TYPE_5__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_PROPV_DECODER_AVCODEC ; 
#define  FFP_PROP_INT64_ASYNC_STATISTIC_BUF_BACKWARDS 150 
#define  FFP_PROP_INT64_ASYNC_STATISTIC_BUF_CAPACITY 149 
#define  FFP_PROP_INT64_ASYNC_STATISTIC_BUF_FORWARDS 148 
#define  FFP_PROP_INT64_AUDIO_CACHED_BYTES 147 
#define  FFP_PROP_INT64_AUDIO_CACHED_DURATION 146 
#define  FFP_PROP_INT64_AUDIO_CACHED_PACKETS 145 
#define  FFP_PROP_INT64_AUDIO_DECODER 144 
#define  FFP_PROP_INT64_BIT_RATE 143 
#define  FFP_PROP_INT64_CACHE_STATISTIC_COUNT_BYTES 142 
#define  FFP_PROP_INT64_CACHE_STATISTIC_FILE_FORWARDS 141 
#define  FFP_PROP_INT64_CACHE_STATISTIC_FILE_POS 140 
#define  FFP_PROP_INT64_CACHE_STATISTIC_PHYSICAL_POS 139 
#define  FFP_PROP_INT64_LATEST_SEEK_LOAD_DURATION 138 
#define  FFP_PROP_INT64_LOGICAL_FILE_SIZE 137 
#define  FFP_PROP_INT64_SELECTED_AUDIO_STREAM 136 
#define  FFP_PROP_INT64_SELECTED_TIMEDTEXT_STREAM 135 
#define  FFP_PROP_INT64_SELECTED_VIDEO_STREAM 134 
#define  FFP_PROP_INT64_TCP_SPEED 133 
#define  FFP_PROP_INT64_TRAFFIC_STATISTIC_BYTE_COUNT 132 
#define  FFP_PROP_INT64_VIDEO_CACHED_BYTES 131 
#define  FFP_PROP_INT64_VIDEO_CACHED_DURATION 130 
#define  FFP_PROP_INT64_VIDEO_CACHED_PACKETS 129 
#define  FFP_PROP_INT64_VIDEO_DECODER 128 
 int /*<<< orphan*/  SDL_SpeedSampler2GetSpeed (int /*<<< orphan*/ *) ; 

int64_t ffp_get_property_int64(FFPlayer *ffp, int id, int64_t default_value)
{
    switch (id) {
        case FFP_PROP_INT64_SELECTED_VIDEO_STREAM:
            if (!ffp || !ffp->is)
                return default_value;
            return ffp->is->video_stream;
        case FFP_PROP_INT64_SELECTED_AUDIO_STREAM:
            if (!ffp || !ffp->is)
                return default_value;
            return ffp->is->audio_stream;
        case FFP_PROP_INT64_SELECTED_TIMEDTEXT_STREAM:
            if (!ffp || !ffp->is)
                return default_value;
            return ffp->is->subtitle_stream;
        case FFP_PROP_INT64_VIDEO_DECODER:
            if (!ffp)
                return default_value;
            return ffp->stat.vdec_type;
        case FFP_PROP_INT64_AUDIO_DECODER:
            return FFP_PROPV_DECODER_AVCODEC;

        case FFP_PROP_INT64_VIDEO_CACHED_DURATION:
            if (!ffp)
                return default_value;
            return ffp->stat.video_cache.duration;
        case FFP_PROP_INT64_AUDIO_CACHED_DURATION:
            if (!ffp)
                return default_value;
            return ffp->stat.audio_cache.duration;
        case FFP_PROP_INT64_VIDEO_CACHED_BYTES:
            if (!ffp)
                return default_value;
            return ffp->stat.video_cache.bytes;
        case FFP_PROP_INT64_AUDIO_CACHED_BYTES:
            if (!ffp)
                return default_value;
            return ffp->stat.audio_cache.bytes;
        case FFP_PROP_INT64_VIDEO_CACHED_PACKETS:
            if (!ffp)
                return default_value;
            return ffp->stat.video_cache.packets;
        case FFP_PROP_INT64_AUDIO_CACHED_PACKETS:
            if (!ffp)
                return default_value;
            return ffp->stat.audio_cache.packets;
        case FFP_PROP_INT64_BIT_RATE:
            return ffp ? ffp->stat.bit_rate : default_value;
        case FFP_PROP_INT64_TCP_SPEED:
            return ffp ? SDL_SpeedSampler2GetSpeed(&ffp->stat.tcp_read_sampler) : default_value;
        case FFP_PROP_INT64_ASYNC_STATISTIC_BUF_BACKWARDS:
            if (!ffp)
                return default_value;
            return ffp->stat.buf_backwards;
        case FFP_PROP_INT64_ASYNC_STATISTIC_BUF_FORWARDS:
            if (!ffp)
                return default_value;
            return ffp->stat.buf_forwards;
        case FFP_PROP_INT64_ASYNC_STATISTIC_BUF_CAPACITY:
            if (!ffp)
                return default_value;
            return ffp->stat.buf_capacity;
        case FFP_PROP_INT64_LATEST_SEEK_LOAD_DURATION:
            return ffp ? ffp->stat.latest_seek_load_duration : default_value;
        case FFP_PROP_INT64_TRAFFIC_STATISTIC_BYTE_COUNT:
            return ffp ? ffp->stat.byte_count : default_value;
        case FFP_PROP_INT64_CACHE_STATISTIC_PHYSICAL_POS:
            if (!ffp)
                return default_value;
            return ffp->stat.cache_physical_pos;
       case FFP_PROP_INT64_CACHE_STATISTIC_FILE_FORWARDS:
            if (!ffp)
                return default_value;
            return ffp->stat.cache_file_forwards;
       case FFP_PROP_INT64_CACHE_STATISTIC_FILE_POS:
            if (!ffp)
                return default_value;
            return ffp->stat.cache_file_pos;
       case FFP_PROP_INT64_CACHE_STATISTIC_COUNT_BYTES:
            if (!ffp)
                return default_value;
            return ffp->stat.cache_count_bytes;
       case FFP_PROP_INT64_LOGICAL_FILE_SIZE:
            if (!ffp)
                return default_value;
            return ffp->stat.logical_file_size;
        default:
            return default_value;
    }
}