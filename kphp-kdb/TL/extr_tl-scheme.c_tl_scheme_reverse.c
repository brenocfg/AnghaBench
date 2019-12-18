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
struct TYPE_3__ {struct tl_scheme_object* cdr; } ;
struct TYPE_4__ {TYPE_1__ p; } ;
struct tl_scheme_object {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct tl_scheme_object obj_empty_list ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_scheme_object_dump (int /*<<< orphan*/ ,struct tl_scheme_object*) ; 
 scalar_t__ tlso_list ; 
 int verbosity ; 

struct tl_scheme_object *tl_scheme_reverse (struct tl_scheme_object *A) {
  if (verbosity >= 3) {
    fprintf (stderr, "(reverse ");
    tl_scheme_object_dump (stderr, A);
    fprintf (stderr, ")\n");
  }
  if (A->type != tlso_list) {
    return NULL;
  }
  struct tl_scheme_object *O = &obj_empty_list, *p, *w;
  for (p = A; p != &obj_empty_list; p = w) {
    assert (p->type == tlso_list);
    w = p->u.p.cdr;
    p->u.p.cdr = O;
    O = p;
  }
  return O;
}