#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  car; struct tl_scheme_object* cdr; } ;
struct TYPE_4__ {TYPE_1__ p; } ;
struct tl_scheme_object {TYPE_2__ u; } ;
struct tl_int_array {int pos; } ;
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 struct tl_scheme_object obj_empty_list ; 
 int /*<<< orphan*/  tl_compiler_clear_errors (struct tl_compiler*) ; 
 int tl_expression_serialize (struct tl_compiler*,int /*<<< orphan*/ ,struct tl_int_array*) ; 
 int /*<<< orphan*/  tl_int_array_init (struct tl_int_array*,int*,int) ; 

int tl_serialize (struct tl_compiler *C, struct tl_scheme_object *expressions, int *out, int olen) {
  struct tl_int_array a;
  tl_compiler_clear_errors (C);
  tl_int_array_init (&a, out, olen);
  struct tl_scheme_object *O = expressions, *p;
  for (p = O; p != &obj_empty_list; p = p->u.p.cdr) {
    int r = tl_expression_serialize (C, p->u.p.car, &a);
    if (r < 0) {
      return r;
    }
  }
  return a.pos;
}