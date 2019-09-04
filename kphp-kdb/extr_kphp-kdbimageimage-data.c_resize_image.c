#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct forth_stack {int top; } ;
struct TYPE_6__ {scalar_t__ severity; } ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_1__ ExceptionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyExceptionInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyImage (int /*<<< orphan*/ *) ; 
 void* FORTH_FAIL ; 
 int /*<<< orphan*/  GetExceptionInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  LanczosFilter ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/ * ResizeImage (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,double,TYPE_1__*) ; 
 scalar_t__ UndefinedException ; 
 int /*<<< orphan*/  free_stack (struct forth_stack*,int,int) ; 
 int /*<<< orphan*/  gm_catch_exception (struct forth_stack*,TYPE_1__*) ; 
 int /*<<< orphan*/  pop_image (struct forth_stack*,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  pop_int (struct forth_stack*,int*,char*) ; 
 int /*<<< orphan*/  push_image (struct forth_stack*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *resize_image (void **IP, struct forth_stack *st) {
  Image *image;
  int old_stack_top = st->top;
  int width, height;
  if (!pop_int (st, &height, "resize_image 3rd")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_int (st, &width, "resize_image 2nd")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_image (st, &image, "resize_image 1st")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  ExceptionInfo exception;
  GetExceptionInfo (&exception);
  Image *r = ResizeImage (image, width, height, LanczosFilter, 1.0, &exception);
  if (exception.severity != UndefinedException) {
    st->top = old_stack_top;
    gm_catch_exception (st, &exception);
    if (r != NULL) {
      DestroyImage (r);
    }
    return FORTH_FAIL;
  }
  DestroyExceptionInfo (&exception);

  free_stack (st, st->top + 1, old_stack_top);

  push_image (st, r);

  NEXT;
}