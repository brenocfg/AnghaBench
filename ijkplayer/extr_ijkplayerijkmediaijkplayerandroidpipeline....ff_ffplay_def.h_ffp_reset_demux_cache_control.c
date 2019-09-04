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
struct TYPE_3__ {void* current_high_water_mark_in_ms; int /*<<< orphan*/  last_high_water_mark_in_ms; int /*<<< orphan*/  next_high_water_mark_in_ms; void* first_high_water_mark_in_ms; int /*<<< orphan*/  high_water_mark_in_bytes; int /*<<< orphan*/  max_buffer_size; int /*<<< orphan*/  min_frames; } ;
typedef  TYPE_1__ FFDemuxCacheControl ;

/* Variables and functions */
 void* DEFAULT_FIRST_HIGH_WATER_MARK_IN_MS ; 
 int /*<<< orphan*/  DEFAULT_HIGH_WATER_MARK_IN_BYTES ; 
 int /*<<< orphan*/  DEFAULT_LAST_HIGH_WATER_MARK_IN_MS ; 
 int /*<<< orphan*/  DEFAULT_MIN_FRAMES ; 
 int /*<<< orphan*/  DEFAULT_NEXT_HIGH_WATER_MARK_IN_MS ; 
 int /*<<< orphan*/  MAX_QUEUE_SIZE ; 

__attribute__((used)) inline static void ffp_reset_demux_cache_control(FFDemuxCacheControl *dcc)
{
    dcc->min_frames                = DEFAULT_MIN_FRAMES;
    dcc->max_buffer_size           = MAX_QUEUE_SIZE;
    dcc->high_water_mark_in_bytes  = DEFAULT_HIGH_WATER_MARK_IN_BYTES;

    dcc->first_high_water_mark_in_ms    = DEFAULT_FIRST_HIGH_WATER_MARK_IN_MS;
    dcc->next_high_water_mark_in_ms     = DEFAULT_NEXT_HIGH_WATER_MARK_IN_MS;
    dcc->last_high_water_mark_in_ms     = DEFAULT_LAST_HIGH_WATER_MARK_IN_MS;
    dcc->current_high_water_mark_in_ms  = DEFAULT_FIRST_HIGH_WATER_MARK_IN_MS;
}