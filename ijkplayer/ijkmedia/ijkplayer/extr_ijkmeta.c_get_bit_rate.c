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
typedef  int int64_t ;
struct TYPE_3__ {int codec_type; int bit_rate; int sample_rate; int channels; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
#define  AVMEDIA_TYPE_ATTACHMENT 132 
#define  AVMEDIA_TYPE_AUDIO 131 
#define  AVMEDIA_TYPE_DATA 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int av_get_bits_per_sample (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t get_bit_rate(AVCodecParameters *codecpar)
{
    int64_t bit_rate;
    int bits_per_sample;

    switch (codecpar->codec_type) {
        case AVMEDIA_TYPE_VIDEO:
        case AVMEDIA_TYPE_DATA:
        case AVMEDIA_TYPE_SUBTITLE:
        case AVMEDIA_TYPE_ATTACHMENT:
            bit_rate = codecpar->bit_rate;
            break;
        case AVMEDIA_TYPE_AUDIO:
            bits_per_sample = av_get_bits_per_sample(codecpar->codec_id);
            bit_rate = bits_per_sample ? codecpar->sample_rate * codecpar->channels * bits_per_sample : codecpar->bit_rate;
            break;
        default:
            bit_rate = 0;
            break;
    }
    return bit_rate;
}