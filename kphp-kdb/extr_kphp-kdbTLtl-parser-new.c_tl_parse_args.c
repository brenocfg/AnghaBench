#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree {scalar_t__ type; int nc; TYPE_1__** c; } ;
struct tl_combinator_tree {int dummy; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct tl_combinator_tree* tl_parse_args134 (TYPE_1__*) ; 
 struct tl_combinator_tree* tl_parse_args2 (TYPE_1__*) ; 
 scalar_t__ type_args ; 
#define  type_args1 131 
#define  type_args2 130 
#define  type_args3 129 
#define  type_args4 128 
 scalar_t__ type_optional_arg_def ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__) ; 

struct tl_combinator_tree *tl_parse_args (struct tree *T) {
  vkprintf (2, "tl_parse_args T->type = %d\n", T->type - type_optional_arg_def);
  assert (T->type == type_args);
  assert (T->nc == 1);
  switch (T->c[0]->type) {
  case type_args1:
    return tl_parse_args134 (T->c[0]);
  case type_args2:
    return tl_parse_args2 (T->c[0]);
  case type_args3:
    return tl_parse_args134 (T->c[0]);
  case type_args4:
    return tl_parse_args134 (T->c[0]);
  default:
    assert (0);
    return 0;
  } 
}