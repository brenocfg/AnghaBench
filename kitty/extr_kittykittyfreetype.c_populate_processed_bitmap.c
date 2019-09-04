#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int pitch; int rows; int /*<<< orphan*/  pixel_mode; int /*<<< orphan*/  width; scalar_t__ buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap_top; } ;
struct TYPE_7__ {int stride; int rows; int needs_free; int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap_top; int /*<<< orphan*/  pixel_mode; int /*<<< orphan*/  width; scalar_t__ start_x; scalar_t__ buf; } ;
typedef  TYPE_1__ ProcessedBitmap ;
typedef  TYPE_2__ FT_GlyphSlotRec ;
typedef  TYPE_3__ FT_Bitmap ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static inline void
populate_processed_bitmap(FT_GlyphSlotRec *slot, FT_Bitmap *bitmap, ProcessedBitmap *ans, bool copy_buf) {
    ans->stride = bitmap->pitch < 0 ? -bitmap->pitch : bitmap->pitch;
    ans->rows = bitmap->rows;
    if (copy_buf) {
        ans->buf = calloc(ans->rows, ans->stride);
        if (!ans->buf) fatal("Out of memory");
        ans->needs_free = true;
        memcpy(ans->buf, bitmap->buffer, ans->rows * ans->stride);
    } else ans->buf = bitmap->buffer;
    ans->start_x = 0; ans->width = bitmap->width;
    ans->pixel_mode = bitmap->pixel_mode;
    ans->bitmap_top = slot->bitmap_top; ans->bitmap_left = slot->bitmap_left;
}