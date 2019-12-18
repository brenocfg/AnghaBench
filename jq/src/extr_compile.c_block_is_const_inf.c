#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* first; } ;
typedef  TYPE_3__ block ;
struct TYPE_6__ {int /*<<< orphan*/  constant; } ;
struct TYPE_7__ {scalar_t__ op; TYPE_1__ imm; } ;

/* Variables and functions */
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ LOADK ; 
 scalar_t__ block_is_single (TYPE_3__) ; 
 scalar_t__ isinf (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number_value (int /*<<< orphan*/ ) ; 

int block_is_const_inf(block b) {
  return (block_is_single(b) && b.first->op == LOADK &&
          jv_get_kind(b.first->imm.constant) == JV_KIND_NUMBER &&
          isinf(jv_number_value(b.first->imm.constant)));
}