#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  constant; } ;
struct TYPE_6__ {TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 scalar_t__ JV_KIND_OBJECT ; 
 int /*<<< orphan*/  MODULEMETA ; 
 int /*<<< orphan*/  block_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inst_block (TYPE_2__*) ; 
 TYPE_2__* inst_new (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

block gen_module(block metadata) {
  inst* i = inst_new(MODULEMETA);
  i->imm.constant = block_const(metadata);
  if (jv_get_kind(i->imm.constant) != JV_KIND_OBJECT)
    i->imm.constant = jv_object_set(jv_object(), jv_string("metadata"), i->imm.constant);
  block_free(metadata);
  return inst_block(i);
}