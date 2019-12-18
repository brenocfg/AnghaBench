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
struct TYPE_3__ {struct tl_scheme_object* car; struct tl_scheme_object* cdr; } ;
struct TYPE_4__ {TYPE_1__ p; } ;
struct tl_scheme_object {scalar_t__ type; TYPE_2__ u; } ;
struct tl_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  indent (struct tl_buffer*,int) ; 
 struct tl_scheme_object obj_empty_list ; 
 int /*<<< orphan*/  tl_scheme_object_contain_list (struct tl_scheme_object*) ; 
 scalar_t__ tl_scheme_object_is_colon_terminated_function (struct tl_scheme_object*) ; 
 int /*<<< orphan*/  tl_scheme_object_sbdump (struct tl_buffer*,struct tl_scheme_object*) ; 
 int /*<<< orphan*/  tl_string_buffer_append_char (struct tl_buffer*,char) ; 
 scalar_t__ tlso_list ; 
 scalar_t__ tlso_open_square_bracket ; 

void tl_scheme_object_sbdump_indent (struct tl_buffer *b, struct tl_scheme_object *O, int depth) {
  char ch, obrace, cbrace;
  struct tl_scheme_object *p;
  if (!tl_scheme_object_contain_list (O)) {
    tl_scheme_object_sbdump (b, O);
    return;
  }
  if (O->u.p.cdr != NULL && O->u.p.car->type == tlso_open_square_bracket) {
    obrace = '[';
    cbrace = ']';
    O = O->u.p.cdr;
    ch = ' ';
  } else {
    obrace = '(';
    cbrace = ')';
    ch = 0;
  }
  tl_string_buffer_append_char (b, obrace);
  for (p = O; p != &obj_empty_list; p = p->u.p.cdr) {
    assert (p->type == tlso_list);
    if (ch != 0) {
      tl_string_buffer_append_char (b, '\n');
      indent (b, depth+1);
    }
    tl_scheme_object_sbdump_indent (b, p->u.p.car, depth + 1);
    ch = tl_scheme_object_is_colon_terminated_function (p->u.p.car) ? 0 : ' ';
  }
  tl_string_buffer_append_char (b, '\n');
  indent (b, depth);
  tl_string_buffer_append_char (b, cbrace);
}