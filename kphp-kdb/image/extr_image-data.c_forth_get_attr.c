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
struct forth_stack {int top; int /*<<< orphan*/ * x; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ImageAttribute ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 void* FORTH_FAIL ; 
 TYPE_1__* GetImageAttribute (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  free_stack (struct forth_stack*,int,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_image (struct forth_stack*,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  pop_str (struct forth_stack*,char**,char*) ; 

__attribute__((used)) static void *forth_get_attr (void **IP, struct forth_stack *st) {
  char *attr;
  Image *image;
  int old_stack_top = st->top;

  if (!pop_str (st, &attr, "getattr: 2nd isn't str")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  if (!pop_image (st, &image, "getattr: 1st isn't image")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  free_stack (st, st->top + 1, old_stack_top);

  const ImageAttribute *a = GetImageAttribute (image, attr);
  if (a == NULL) {
    st->top++;
    new_str (&st->x[st->top], "NULL", 0);
  } else {
    char *b = malloc (a->length+1); assert (b);
    memcpy (b, a->value, a->length);
    b[a->length] = 0;
    st->top++;
    new_str (&st->x[st->top], b, 0);
  }

  NEXT;
}