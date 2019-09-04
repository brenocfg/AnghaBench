#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tree {scalar_t__ type; int nc; TYPE_1__** c; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int tl_parse_final_empty (TYPE_1__*) ; 
 int tl_parse_final_final (TYPE_1__*) ; 
 int tl_parse_final_new (TYPE_1__*) ; 
 scalar_t__ type_final_decl ; 
#define  type_final_empty 130 
#define  type_final_final 129 
#define  type_final_new 128 

int tl_parse_final_decl (struct tree *T, int fun) {
  assert (T->type == type_final_decl);
  assert (!fun);
  assert (T->nc == 1);
  switch (T->c[0]->type) {
  case type_final_new:
    return tl_parse_final_new (T->c[0]);
  case type_final_final:
    return tl_parse_final_final (T->c[0]);
  case type_final_empty:
    return tl_parse_final_empty (T->c[0]);
  default:
    assert (0);
    return 0;
  }
}