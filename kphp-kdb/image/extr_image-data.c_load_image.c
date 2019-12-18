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
struct forth_stack {int top; } ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 void* FORTH_FAIL ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  free_stack (struct forth_stack*,int,int) ; 
 int /*<<< orphan*/ * gm_read_image (struct forth_stack*,char*) ; 
 int /*<<< orphan*/  pop_str (struct forth_stack*,char**,char*) ; 
 int /*<<< orphan*/  push_image (struct forth_stack*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

__attribute__((used)) static void *load_image (void **IP, struct forth_stack *st) {
  vkprintf (3, "load_image\n");
  char *filename;
  int old_stack_top = st->top;
  if (!pop_str (st, &filename, "read_image 1st")) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }
  Image *r = gm_read_image (st, filename);

  if (r == NULL) {
    st->top = old_stack_top;
    return FORTH_FAIL;
  }

  free_stack (st, st->top + 1, old_stack_top);

  push_image (st, r);

  NEXT;
}