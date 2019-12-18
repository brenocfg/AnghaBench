#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_8__ {int /*<<< orphan*/  constant; } ;
struct TYPE_9__ {scalar_t__ op; struct TYPE_9__* next; TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
struct TYPE_10__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; TYPE_2__* first; } ;
typedef  TYPE_3__ block ;

/* Variables and functions */
 scalar_t__ INSERT ; 
 scalar_t__ JV_KIND_STRING ; 
 scalar_t__ LOADK ; 
 scalar_t__ PUSHK_UNDER ; 
 scalar_t__ SUBEXP_BEGIN ; 
 scalar_t__ SUBEXP_END ; 
 int /*<<< orphan*/  block_free (TYPE_3__) ; 
 TYPE_3__ gen_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

block gen_const_object(block expr) {
  int is_const = 1;
  jv o = jv_object();
  jv k = jv_null();
  jv v = jv_null();
  for (inst *i = expr.first; i; i = i->next) {
    if (i->op == PUSHK_UNDER) {
      k = jv_copy(i->imm.constant);
      i = i->next;
    } else if (i->op != SUBEXP_BEGIN ||
        i->next == NULL ||
        i->next->op != LOADK ||
        i->next->next == NULL ||
        i->next->next->op != SUBEXP_END) {
      is_const = 0;
      break;
    } else {
      k = jv_copy(i->next->imm.constant);
      i = i->next->next->next;
    }
    if (i != NULL && i->op == PUSHK_UNDER) {
      v = jv_copy(i->imm.constant);
      i = i->next;
    } else if (i == NULL ||
        i->op != SUBEXP_BEGIN ||
        i->next == NULL ||
        i->next->op != LOADK ||
        i->next->next == NULL ||
        i->next->next->op != SUBEXP_END) {
      is_const = 0;
      break;
    } else {
      v = jv_copy(i->next->imm.constant);
      i = i->next->next->next;
    }
    if (i == NULL || i->op != INSERT) {
      is_const = 0;
      break;
    }
    if (jv_get_kind(k) != JV_KIND_STRING) {
      is_const = 0;
      break;
    }
    o = jv_object_set(o, k, v);
    k = jv_null();
    v = jv_null();
  }
  if (!is_const) {
    jv_free(o);
    jv_free(k);
    jv_free(v);
    block b = {0,0};
    return b;
  }
  block_free(expr);
  return gen_const(o);
}