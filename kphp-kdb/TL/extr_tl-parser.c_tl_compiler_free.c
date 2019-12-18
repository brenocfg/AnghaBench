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
struct tl_compiler {int /*<<< orphan*/  hm_composite_typename; int /*<<< orphan*/ * hm_combinator; int /*<<< orphan*/ * hm_magic; int /*<<< orphan*/  tmp_error_buff; int /*<<< orphan*/ * error_msg; } ;

/* Variables and functions */
 int TL_MAX_ERRORS ; 
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_hashmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_list_expressions_free (struct tl_compiler*,int) ; 
 int /*<<< orphan*/  tl_string_buffer_free (int /*<<< orphan*/ *) ; 

void tl_compiler_free (struct tl_compiler *C) {
  int i;
  for (i = 0; i < TL_MAX_ERRORS; i++) {
    cstr_free (&C->error_msg[i]);
  }
  tl_string_buffer_free (&C->tmp_error_buff);
  for (i = 0; i < 2; i++) {
    tl_list_expressions_free (C, i);
    tl_hashmap_free (&C->hm_magic[i]);
    tl_hashmap_free (&C->hm_combinator[i]);
  }
  tl_hashmap_free (&C->hm_composite_typename);
}