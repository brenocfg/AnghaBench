#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_var_value_t ;
struct tl_constructor {int name; scalar_t__ right; scalar_t__ left; int /*<<< orphan*/  id; TYPE_1__* type; } ;
struct TYPE_2__ {int name; } ;

/* Variables and functions */
 int TLS_COMBINATOR_LEFT ; 
 int TLS_COMBINATOR_LEFT_BUILTIN ; 
 int TLS_COMBINATOR_RIGHT ; 
 int TLS_COMBINATOR_RIGHT_V2 ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ is_builtin_type (int /*<<< orphan*/ ) ; 
 int schema_version ; 
 int /*<<< orphan*/  wint (int) ; 
 int /*<<< orphan*/  write_tree (scalar_t__,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  wstr (int /*<<< orphan*/ ) ; 

void write_combinator (struct tl_constructor *c) {
  wint (c->name);
  wstr (c->id);
  wint (c->type ? c->type->name : 0);
  tree_var_value_t *T = 0;
  int x = 0;
  assert (c->right);
  if (c->left) {
    if (schema_version >= 1 && is_builtin_type (c->id)) {
      wint (TLS_COMBINATOR_LEFT_BUILTIN);
    } else {
      if (schema_version >= 1) {
        wint (TLS_COMBINATOR_LEFT);
      }
//      wint (count_list_size (c->left));
      write_tree (c->left, 0, &T, &x);
    }
  } else {
    if (schema_version >= 1) {
      wint (TLS_COMBINATOR_LEFT);
      wint (0);
    } else {
      wint (-11);
    }
  }
  if (schema_version >= 1) {
    wint (schema_version >= 2 ? TLS_COMBINATOR_RIGHT_V2 : TLS_COMBINATOR_RIGHT);
  }
  write_tree (c->right, 1, &T, &x);
}