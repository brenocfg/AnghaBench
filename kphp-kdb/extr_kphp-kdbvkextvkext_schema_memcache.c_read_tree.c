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
#define  TLS_TREE_ARRAY 132 
#define  TLS_TREE_NAT_CONST 131 
#define  TLS_TREE_NAT_VAR 130 
#define  TLS_TREE_TYPE 129 
#define  TLS_TREE_TYPE_VAR 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct tl_tree* read_array (int*) ; 
 struct tl_tree* read_num_const (int*) ; 
 struct tl_tree* read_num_var (int*) ; 
 struct tl_tree* read_type (int*) ; 
 struct tl_tree* read_type_var (int*) ; 
 int /*<<< orphan*/  stderr ; 
 int tl_parse_int () ; 
 int verbosity ; 

struct tl_tree *read_tree (int *var_num) {
  int x = tl_parse_int ();
  if (verbosity >= 2) {
    fprintf (stderr, "read_tree: constructor = 0x%08x\n", x);
  }
  switch (x) {
  case TLS_TREE_NAT_CONST:
    return read_num_const (var_num);
  case TLS_TREE_NAT_VAR:
    return read_num_var (var_num);
  case TLS_TREE_TYPE_VAR:
    return read_type_var (var_num);
  case TLS_TREE_TYPE:
    return read_type (var_num);
  case TLS_TREE_ARRAY:
    return read_array (var_num);
  default:
    if (verbosity) {
      fprintf (stderr, "x = %d\n", x);
    }
    return 0;
  }    
}