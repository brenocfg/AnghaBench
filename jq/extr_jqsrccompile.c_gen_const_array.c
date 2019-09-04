#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_11__ {TYPE_1__* target; int /*<<< orphan*/  constant; } ;
struct TYPE_13__ {scalar_t__ op; TYPE_2__ imm; struct TYPE_13__* next; } ;
typedef  TYPE_4__ inst ;
struct TYPE_14__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; TYPE_3__* last; TYPE_4__* first; } ;
typedef  TYPE_5__ block ;
struct TYPE_12__ {scalar_t__ op; } ;
struct TYPE_10__ {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ FORK ; 
 scalar_t__ JUMP ; 
 scalar_t__ LOADK ; 
 int /*<<< orphan*/  block_free (TYPE_5__) ; 
 TYPE_5__ gen_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block gen_const_array(block expr) {
  /*
   * An expr of all constant elements looks like this:
   *
   * 0009 FORK 0027
   * 0011 FORK 0023
   * 0013 FORK 0019
   * 0015 LOADK 1
   * 0017 JUMP 0021
   * 0019 LOADK 2
   * 0021 JUMP 0025
   * 0023 LOADK 3
   * 0025 JUMP 0029
   * 0027 LOADK 4
   *
   * That's: N-1 commas for N elements, N LOADKs, and a JUMP between
   * every LOADK.  The sequence ends in a LOADK.  Any deviation and it's
   * not a list of constants.
   *
   * Here we check for this pattern almost exactly.  We don't check that
   * the targets of the FORK and JUMP instructions are in the right
   * sequence.
   */
  int all_const = 1;
  int commas = 0;
  int normal = 1;
  jv a = jv_array();
  for (inst *i = expr.first; i; i = i->next) {
    if (i->op == FORK) {
      commas++;
      if (i->imm.target == NULL || i->imm.target->op != JUMP ||
          jv_array_length(jv_copy(a)) > 0) {
        normal = 0;
        break;
      }
    } else if (all_const && i->op == LOADK) {
      if (i->next != NULL && i->next->op != JUMP) {
        normal = 0;
        break;
      }
      a = jv_array_append(a, jv_copy(i->imm.constant));
    } else if (i->op != JUMP || i->imm.target == NULL ||
               i->imm.target->op != LOADK) {
      all_const = 0;
    }
  }

  if (all_const && normal &&
      (expr.last == NULL || expr.last->op == LOADK) &&
      jv_array_length(jv_copy(a)) == commas + 1) {
    block_free(expr);
    return gen_const(a);
  }

  jv_free(a);
  block b = {0,0};
  return b;
}