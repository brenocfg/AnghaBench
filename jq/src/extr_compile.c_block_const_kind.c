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
typedef  int /*<<< orphan*/  jv_kind ;
struct TYPE_8__ {TYPE_2__* first; } ;
typedef  TYPE_3__ block ;
struct TYPE_6__ {int /*<<< orphan*/  constant; } ;
struct TYPE_7__ {TYPE_1__ imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_is_const (TYPE_3__) ; 
 int /*<<< orphan*/  jv_get_kind (int /*<<< orphan*/ ) ; 

jv_kind block_const_kind(block b) {
  assert(block_is_const(b));
  return jv_get_kind(b.first->imm.constant);
}