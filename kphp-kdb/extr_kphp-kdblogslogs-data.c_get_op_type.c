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
typedef  int /*<<< orphan*/  val_type ;
typedef  int token_type ;

/* Variables and functions */
 scalar_t__ IS_STR (int /*<<< orphan*/ ) ; 
#define  op_bit_count 139 
#define  op_color 138 
#define  op_double 137 
#define  op_in 136 
#define  op_int 135 
 int op_length ; 
#define  op_long 134 
#define  op_now 133 
 int op_rem ; 
 int op_shl ; 
#define  op_string 132 
 int* op_type ; 
 int op_type_to_id ; 
#define  t_arif 131 
#define  t_bin 130 
#define  t_cmp 129 
#define  t_logic 128 
 int t_str ; 
 int /*<<< orphan*/  v_cstring ; 
 int /*<<< orphan*/  v_double ; 
 int /*<<< orphan*/  v_err ; 
 int /*<<< orphan*/  v_int ; 
 int /*<<< orphan*/  v_long ; 

inline val_type get_op_type (val_type a, token_type op) {
  switch (op) {
    case op_color:
    case op_in:
    case op_bit_count:
      if (a != v_int && a != v_long) {
        return v_err;
      }
    case op_now:
    case op_int:
      return v_int;
    case op_long:
      return v_long;
    case op_double:
      return v_double;
    case op_string:
      return v_cstring;
    default:
      break;
  }

  if (IS_STR(a)) {
    if (op_type[op] == t_cmp || op == op_shl || op == op_length || op == op_type_to_id) {
      return v_int;
    }
    if (op_type[op] == t_str) {
      return v_cstring;
    }
    return v_err;
  }

  switch (op_type[op]) {
    case t_arif:
      if (op == op_rem && a == v_double) {
        return v_err;
      }
      return a;
    case t_logic:
      if (a == v_double) {
        return v_err;
      }
      return v_int;
    case t_bin:
      if (a == v_double) {
        return v_err;
      }
      return a;
    case t_cmp:
      return v_int;
    default:
      return v_err;
  }
  return v_err;
}