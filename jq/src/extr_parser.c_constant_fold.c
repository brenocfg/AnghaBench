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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
#define  EQ 131 
#define  GREATEREQ 130 
 scalar_t__ JV_KIND_INVALID ; 
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_STRING ; 
#define  LESSEQ 129 
#define  NEQ 128 
 int /*<<< orphan*/  block_const (int /*<<< orphan*/ ) ; 
 scalar_t__ block_const_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_is_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_is_single (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int jv_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_false () ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/  jv_number (double) ; 
 double jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_true () ; 

__attribute__((used)) static block constant_fold(block a, block b, int op) {
  if (!block_is_single(a) || !block_is_const(a) ||
      !block_is_single(b) || !block_is_const(b))
    return gen_noop();
  if (op == '+') {
    if (block_const_kind(a) == JV_KIND_NULL) {
      block_free(a);
      return b;
    }
    if (block_const_kind(b) == JV_KIND_NULL) {
      block_free(b);
      return a;
    }
  }
  if (block_const_kind(a) != block_const_kind(b))
    return gen_noop();

  jv res = jv_invalid();

  if (block_const_kind(a) == JV_KIND_NUMBER) {
    jv jv_a = block_const(a);
    jv jv_b = block_const(b);

    double na = jv_number_value(jv_a);
    double nb = jv_number_value(jv_b);

    int cmp = jv_cmp(jv_a, jv_b);

    switch (op) {
    case '+': res = jv_number(na + nb); break;
    case '-': res = jv_number(na - nb); break;
    case '*': res = jv_number(na * nb); break;
    case '/': res = jv_number(na / nb); break;
    case EQ:  res = (cmp == 0 ? jv_true() : jv_false()); break;
    case NEQ: res = (cmp != 0 ? jv_true() : jv_false()); break;
    case '<': res = (cmp < 0 ? jv_true() : jv_false()); break;
    case '>': res = (cmp > 0 ? jv_true() : jv_false()); break;
    case LESSEQ: res = (cmp <= 0 ? jv_true() : jv_false()); break;
    case GREATEREQ: res = (cmp >= 0 ? jv_true() : jv_false()); break;
    default: break;
    }
  } else if (op == '+' && block_const_kind(a) == JV_KIND_STRING) {
    res = jv_string_concat(block_const(a),  block_const(b));
  } else {
    return gen_noop();
  }

  if (jv_get_kind(res) == JV_KIND_INVALID)
    return gen_noop();

  block_free(a);
  block_free(b);
  return gen_const(res);
}