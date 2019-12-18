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
struct forth_stack {int top; } ;
struct TYPE_3__ {int x; int y; int width; int height; } ;
typedef  TYPE_1__ RectangleInfo ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 void* FORTH_FAIL ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  free_stack (struct forth_stack*,int,int) ; 
 int /*<<< orphan*/ * gm_crop_image (struct forth_stack*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pop_image (struct forth_stack*,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  pop_int (struct forth_stack*,int*,char*) ; 
 int /*<<< orphan*/  push_image (struct forth_stack*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *crop_image (void **IP, struct forth_stack *st) {
  int old_stack_top = st->top;
  int x, y, width, height;
  Image *image;

  if (!pop_int (st, &height, "crop_image 5th")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_int (st, &width, "crop_image 4th")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_int (st, &y, "crop_image 3rd")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_int (st, &x, "crop_image 2nd")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_image (st, &image, "crop_image 1st")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }
  RectangleInfo rect;
  rect.x = x;
  rect.y = y;
  rect.width = width;
  rect.height = height;
  Image *r = gm_crop_image (st, image, &rect);
  if (r == NULL) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  free_stack (st, st->top + 1, old_stack_top);

  push_image (st, r);

  NEXT;

}