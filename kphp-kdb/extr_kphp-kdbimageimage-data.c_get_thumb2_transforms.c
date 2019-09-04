#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thumb2 {int width; int max_height; int min_height; } ;
struct TYPE_5__ {int width; int height; int x; int y; } ;
typedef  TYPE_1__ RectangleInfo ;

/* Variables and functions */
 int THUMB2_CROP_MASK ; 
 int THUMB2_RESIZE_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int resize_height (int,int,int) ; 

__attribute__((used)) static int get_thumb2_transforms (int width, int height, struct thumb2 *u, RectangleInfo *resize_rect, RectangleInfo *crop_rect) {
  memset (resize_rect, 0, sizeof (RectangleInfo));
  memset (crop_rect, 0, sizeof (RectangleInfo));
  int r = 0;
  if (width <= u->width) {
    if (height > u->max_height) {
      r |= THUMB2_CROP_MASK;
      crop_rect->width = width;
      crop_rect->height = u->max_height;
      crop_rect->x = crop_rect->y = 0;
    }
    return r;
  }
  int y = resize_height (width, u->width, height);
  if (y >= u->min_height) {
    r |= THUMB2_RESIZE_MASK;
    resize_rect->width = u->width;
    resize_rect->height = y;
    if (y > u->max_height) {
      r |= THUMB2_CROP_MASK;
      crop_rect->width = u->width;
      crop_rect->height = u->max_height;
      crop_rect->x = crop_rect->y = 0;
    }
    return r;
  }
  if (height < u->min_height) {
    crop_rect->width = u->width;
    crop_rect->height = height;
    crop_rect->x = (width - u->width) / 2;
    crop_rect->y = 0;
    return THUMB2_CROP_MASK;
  }
  assert (width > u->width && height >= u->min_height);
  int x = resize_height (height, u->min_height, width);
  resize_rect->width = x;
  resize_rect->height = u->min_height;
  crop_rect->width = u->width;
  crop_rect->height = u->min_height;
  crop_rect->x = (x - u->width) / 2;
  crop_rect->y = 0;
  return THUMB2_RESIZE_MASK | THUMB2_CROP_MASK;
}