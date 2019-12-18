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
struct tl_tree {int dummy; } ;

/* Variables and functions */
#define  TLS_EXPR_NAT 129 
#define  TLS_EXPR_TYPE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct tl_tree* read_nat_expr (int*) ; 
 struct tl_tree* read_type_expr (int*) ; 
 int /*<<< orphan*/  stderr ; 
 int tl_parse_int () ; 
 int verbosity ; 

struct tl_tree *read_expr (int *var_num) {
  int x = tl_parse_int ();
  if (verbosity >= 2) {
    fprintf (stderr, "read_nat_expr: constructor = 0x%08x\n", x);
  }
  switch (x) {
  case TLS_EXPR_NAT:
    return read_nat_expr (var_num);
  case TLS_EXPR_TYPE:
    return read_type_expr (var_num);
  default:
    if (verbosity) {
      fprintf (stderr, "x = %d\n", x);
    }
    return 0;
  }
}