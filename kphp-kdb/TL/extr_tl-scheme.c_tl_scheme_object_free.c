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
struct TYPE_3__ {struct tl_scheme_object* cdr; struct tl_scheme_object* car; } ;
struct TYPE_4__ {int /*<<< orphan*/  s; TYPE_1__ p; } ;
struct tl_scheme_object {int type; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 struct tl_scheme_object obj_empty_list ; 
#define  tlso_double 135 
#define  tlso_function 134 
#define  tlso_int 133 
#define  tlso_list 132 
#define  tlso_long 131 
#define  tlso_open_round_bracket 130 
#define  tlso_open_square_bracket 129 
#define  tlso_str 128 
 int /*<<< orphan*/  zfree (struct tl_scheme_object*,int) ; 

void tl_scheme_object_free (struct tl_scheme_object *A) {
  switch (A->type) {
    case tlso_list:
      if (A != &obj_empty_list) {
        tl_scheme_object_free (A->u.p.car);
        if (A->u.p.cdr != &obj_empty_list) {
          tl_scheme_object_free (A->u.p.cdr);
        }
      }
    break;
    case tlso_str:
    case tlso_function:
      cstr_free (&A->u.s);
    break;
    case tlso_open_round_bracket:
    case tlso_open_square_bracket:
      return;
    case tlso_int:
    case tlso_long:
    case tlso_double:
    break;
  }
  zfree (A, sizeof (struct tl_scheme_object));
}