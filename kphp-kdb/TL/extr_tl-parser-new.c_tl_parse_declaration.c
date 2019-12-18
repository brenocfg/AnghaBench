#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tree {scalar_t__ type; int nc; TYPE_1__** c; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int tl_parse_builtin_combinator_decl (TYPE_1__*,int) ; 
 int tl_parse_combinator_decl (TYPE_1__*,int) ; 
 int tl_parse_final_decl (TYPE_1__*,int) ; 
 int tl_parse_partial_app_decl (TYPE_1__*,int) ; 
#define  type_builtin_combinator_decl 131 
#define  type_combinator_decl 130 
 scalar_t__ type_declaration ; 
#define  type_final_decl 129 
#define  type_partial_app_decl 128 

int tl_parse_declaration (struct tree *T, int fun) {
  assert (T->type == type_declaration);
  assert (T->nc == 1);
  switch (T->c[0]->type) {
  case type_combinator_decl:
    return tl_parse_combinator_decl (T->c[0], fun);
  case type_partial_app_decl:
    return tl_parse_partial_app_decl (T->c[0], fun);
  case type_final_decl:
    return tl_parse_final_decl (T->c[0], fun);
  case type_builtin_combinator_decl:
    return tl_parse_builtin_combinator_decl (T->c[0], fun);
  default:
    assert (0);
    return 0;
  }
}