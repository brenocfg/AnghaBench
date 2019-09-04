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
struct tree {scalar_t__ type; int nc; int /*<<< orphan*/ * c; } ;
struct tl_combinator_tree {int dummy; } ;

/* Variables and functions */
 struct tl_combinator_tree* L ; 
 int /*<<< orphan*/  TL_INIT (struct tl_combinator_tree*) ; 
 int /*<<< orphan*/  TL_TRY (int /*<<< orphan*/ ,struct tl_combinator_tree*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_parse_subexpr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ type_expr ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

struct tl_combinator_tree *tl_parse_expr (struct tree *T, int s) {
  assert (T->type == type_expr);
  assert (T->nc >= 1);
  vkprintf (2, "tl_parse_expr: s = %d\n", s);
  int i;
  TL_INIT (L);
  for (i = 0; i < T->nc; i++) {
    TL_TRY (tl_parse_subexpr (T->c[i], s), L);
    s = 0;
  }
  return L;
}