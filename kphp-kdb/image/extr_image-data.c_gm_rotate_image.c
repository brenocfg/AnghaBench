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
struct forth_stack {int dummy; } ;
struct TYPE_6__ {scalar_t__ severity; } ;
typedef  int /*<<< orphan*/  Image ;
typedef  TYPE_1__ ExceptionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyExceptionInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExceptionInfo (TYPE_1__*) ; 
 int /*<<< orphan*/ * ReferenceImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RotateImage (int /*<<< orphan*/ *,double,TYPE_1__*) ; 
 scalar_t__ UndefinedException ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gm_catch_exception (struct forth_stack*,TYPE_1__*) ; 

__attribute__((used)) static Image *gm_rotate_image (struct forth_stack *st, Image *image, int angle) {
  assert (angle >= 0 && angle < 360);
  if (angle == 0) {
    return ReferenceImage (image);
  }
  ExceptionInfo exception;
  GetExceptionInfo (&exception);
  Image *r = RotateImage (image, (double) angle, &exception);
  if (exception.severity != UndefinedException) {
    gm_catch_exception (st, &exception);
    if (r != NULL) {
      DestroyImage (r);
    }
    return 0;
  }
  DestroyExceptionInfo (&exception);
  return r;
}