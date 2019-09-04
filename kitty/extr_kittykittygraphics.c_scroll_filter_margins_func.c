#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {int height; } ;
struct TYPE_10__ {scalar_t__ start_row; int src_height; int src_y; scalar_t__ effective_num_rows; } ;
struct TYPE_9__ {int margin_top; scalar_t__ margin_bottom; scalar_t__ amt; } ;
typedef  TYPE_1__ ScrollData ;
typedef  TYPE_2__ ImageRef ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_3__ CellPixelSize ;

/* Variables and functions */
 int ref_outside_region (TYPE_2__*,int,scalar_t__) ; 
 scalar_t__ ref_within_region (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  update_src_rect (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
scroll_filter_margins_func(ImageRef* ref, Image* img, const void* data, CellPixelSize cell) {
    ScrollData *d = (ScrollData*)data;
    if (ref_within_region(ref, d->margin_top, d->margin_bottom)) {
        ref->start_row += d->amt;
        if (ref_outside_region(ref, d->margin_top, d->margin_bottom)) return true;
        // Clip the image if scrolling has resulted in part of it being outside the page area
        uint32_t clip_amt, clipped_rows;
        if (ref->start_row < (int32_t)d->margin_top) {
            // image moved up
            clipped_rows = d->margin_top - ref->start_row;
            clip_amt = cell.height * clipped_rows;
            if (ref->src_height <= clip_amt) return true;
            ref->src_y += clip_amt; ref->src_height -= clip_amt;
            ref->effective_num_rows -= clipped_rows;
            update_src_rect(ref, img);
            ref->start_row += clipped_rows;
        } else if (ref->start_row + ref->effective_num_rows > d->margin_bottom) {
            // image moved down
            clipped_rows = ref->start_row + ref->effective_num_rows - d->margin_bottom;
            clip_amt = cell.height * clipped_rows;
            if (ref->src_height <= clip_amt) return true;
            ref->src_height -= clip_amt;
            ref->effective_num_rows -= clipped_rows;
            update_src_rect(ref, img);
        }
        return ref_outside_region(ref, d->margin_top, d->margin_bottom);
    }
    return false;
}