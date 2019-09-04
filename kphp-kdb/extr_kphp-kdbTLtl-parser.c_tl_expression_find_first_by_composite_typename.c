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
struct tl_expression {char* right_name; } ;
struct tl_compiler {int /*<<< orphan*/  hm_composite_typename; } ;

/* Variables and functions */
 struct tl_expression* tl_hashmap_get_f (int /*<<< orphan*/ *,struct tl_expression*,int /*<<< orphan*/ ) ; 

struct tl_expression *tl_expression_find_first_by_composite_typename (struct tl_compiler *C, char *composite_typename) {
  struct tl_expression T = { .right_name = composite_typename };
  return tl_hashmap_get_f (&C->hm_composite_typename, &T, 0);
}