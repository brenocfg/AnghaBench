#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thumb2 {int width; int max_height; } ;

/* Variables and functions */

__attribute__((used)) static int thumbs2_want_resize (int width, int height, struct thumb2 *u) {
  return width >= u->width && height >= u->max_height;
  /*
  RectangleInfo resize_rect, crop_rect;
  int res = get_thumb2_transforms (width, height, u, &resize_rect, &crop_rect);
  return (res & THUMB2_RESIZE_MASK) ? 1 : 0;
  */
}