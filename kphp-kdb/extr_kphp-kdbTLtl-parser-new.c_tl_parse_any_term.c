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
struct tree {int type; } ;
struct tl_combinator_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 struct tl_combinator_tree* tl_parse_expr (struct tree*,int) ; 
 struct tl_combinator_tree* tl_parse_ident (struct tree*,int) ; 
 struct tl_combinator_tree* tl_parse_nat_const (struct tree*,int) ; 
 struct tl_combinator_tree* tl_parse_nat_term (struct tree*,int) ; 
 struct tl_combinator_tree* tl_parse_subexpr (struct tree*,int) ; 
 struct tl_combinator_tree* tl_parse_term (struct tree*,int) ; 
 struct tl_combinator_tree* tl_parse_type_term (struct tree*,int) ; 
#define  type_expr 135 
#define  type_nat_const 134 
#define  type_nat_term 133 
#define  type_subexpr 132 
#define  type_term 131 
#define  type_type_ident 130 
#define  type_type_term 129 
#define  type_var_ident 128 

struct tl_combinator_tree *tl_parse_any_term (struct tree *T, int s) {
  switch (T->type) {
  case type_type_term:
    return tl_parse_type_term (T, s);
  case type_nat_term:
    return tl_parse_nat_term (T, s);
  case type_term:
    return tl_parse_term (T, s);
  case type_expr:
    return tl_parse_expr (T, s);
  case type_subexpr:
    return tl_parse_subexpr (T, s);
  case type_nat_const:
    return tl_parse_nat_const (T, s);
  case type_type_ident:
  case type_var_ident:
    return tl_parse_ident (T, s);
  default:
    fprintf (stderr, "type = %d\n", T->type);
    assert (0);
    return 0;    
  }
}