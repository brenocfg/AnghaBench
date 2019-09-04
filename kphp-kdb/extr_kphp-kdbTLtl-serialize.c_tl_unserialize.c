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
struct tl_scheme_object {int dummy; } ;
struct tl_compiler {int dummy; } ;
struct tl_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_compiler_clear_errors (struct tl_compiler*) ; 
 int tl_expression_unserialize (struct tl_compiler*,int*,int,int,int /*<<< orphan*/ *,struct tl_scheme_object**) ; 
 int /*<<< orphan*/  tl_scheme_object_free (struct tl_scheme_object*) ; 
 int /*<<< orphan*/  tl_scheme_object_sbdump (struct tl_buffer*,struct tl_scheme_object*) ; 

int tl_unserialize (struct tl_compiler *C, struct tl_buffer *b, int *input, int ilen, int section_mask) {
  struct tl_scheme_object *O = NULL;
  tl_compiler_clear_errors (C);
  int r = tl_expression_unserialize (C, input, ilen, section_mask, NULL, &O);
  if (r >= 0 && O != NULL) {
    tl_scheme_object_sbdump (b, O);
    tl_scheme_object_free (O);
  }
  return r;
}