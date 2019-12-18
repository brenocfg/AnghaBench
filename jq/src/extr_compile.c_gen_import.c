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
typedef  int /*<<< orphan*/  jv ;
struct TYPE_5__ {int /*<<< orphan*/  constant; } ;
struct TYPE_6__ {TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  DEPS ; 
 int /*<<< orphan*/  inst_block (TYPE_2__*) ; 
 TYPE_2__* inst_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_false () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char const*) ; 
 int /*<<< orphan*/  jv_true () ; 

block gen_import(const char* name, const char* as, int is_data) {
  inst* i = inst_new(DEPS);
  jv meta = jv_object();
  if (as != NULL)
    meta = jv_object_set(meta, jv_string("as"), jv_string(as));
  meta = jv_object_set(meta, jv_string("is_data"), is_data ? jv_true() : jv_false());
  meta = jv_object_set(meta, jv_string("relpath"), jv_string(name));
  i->imm.constant = meta;
  return inst_block(i);
}