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
struct TYPE_4__ {char* s; TYPE_1__ p; } ;
struct tl_scheme_object {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct tl_scheme_object obj_empty_list ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ tlso_list ; 
 scalar_t__ tlso_str ; 

__attribute__((used)) static char *get_raw_scheme (struct tl_scheme_object *O) {
  if (O->type != tlso_list) {
    return NULL;
  }
  struct tl_scheme_object *A = O->u.p.cdr;
  if (A == &obj_empty_list) {
    return NULL;
  }
  assert (A->type == tlso_list);
  struct tl_scheme_object *B = A->u.p.car;
  //tl_scheme_object_dump (stdout, B);
  if (B->type == tlso_str && strcmp (B->u.s, "raw_scheme:")) {
    return NULL;
  }
  struct tl_scheme_object *C = A->u.p.cdr;
  if (C->type != tlso_list) {
    return NULL;
  }
  struct tl_scheme_object *D = C->u.p.car;
  if (D->type != tlso_str) {
    return NULL;
  }
  return D->u.s;
}