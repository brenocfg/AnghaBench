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
struct forth_stack {int top; } ;
struct TYPE_5__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ ImageInfo ;
typedef  int /*<<< orphan*/  Image ;
typedef  int /*<<< orphan*/  ExceptionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CatchException (int /*<<< orphan*/ *) ; 
 TYPE_1__* CloneImageInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyExceptionInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyImageInfo (TYPE_1__*) ; 
 void* FORTH_FAIL ; 
 int /*<<< orphan*/  GetExceptionInfo (int /*<<< orphan*/ *) ; 
 int MaxTextExtent ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/ * PingImage (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* failf (struct forth_stack*,char*,...) ; 
 int /*<<< orphan*/  free_stack (struct forth_stack*,int,int) ; 
 int /*<<< orphan*/  pop_str (struct forth_stack*,char**,char*) ; 
 int /*<<< orphan*/  push_image (struct forth_stack*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void *forth_ping (void **IP, struct forth_stack *st) {
  char *filename;
  int old_stack_top = st->top;
  if (!pop_str (st, &filename, "ping: 1st isn't str")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }
  if (strlen (filename) > MaxTextExtent-1) {
    return failf (st, "ping: filename too long");
  }
  ExceptionInfo exception;
  GetExceptionInfo (&exception);
  ImageInfo *image_info = CloneImageInfo (NULL);
  strcpy (image_info->filename, filename);
  Image *r = PingImage (image_info, &exception);
  DestroyImageInfo (image_info);
  if (r == NULL) {
    st->top = old_stack_top;
    CatchException (&exception);
    DestroyExceptionInfo (&exception);
    return failf (st, "ping: PingImage (%s) throws exception", filename);
  }

  free_stack (st, st->top + 1, old_stack_top);

  push_image (st, r);

  NEXT;
}