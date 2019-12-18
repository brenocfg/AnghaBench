#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  constant; } ;
struct TYPE_13__ {scalar_t__ op; TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
struct TYPE_14__ {TYPE_2__* first; } ;
typedef  TYPE_3__ block ;

/* Variables and functions */
 scalar_t__ DEPS ; 
 scalar_t__ JV_KIND_OBJECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_const (TYPE_3__) ; 
 scalar_t__ block_const_kind (TYPE_3__) ; 
 int /*<<< orphan*/  block_free (TYPE_3__) ; 
 scalar_t__ block_is_const (TYPE_3__) ; 
 scalar_t__ block_is_single (TYPE_3__) ; 
 int /*<<< orphan*/  jv_object_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

block gen_import_meta(block import, block metadata) {
  assert(block_is_single(import) && import.first->op == DEPS);
  assert(block_is_const(metadata) && block_const_kind(metadata) == JV_KIND_OBJECT);
  inst *i = import.first;
  i->imm.constant = jv_object_merge(block_const(metadata), i->imm.constant);
  block_free(metadata);
  return import;
}