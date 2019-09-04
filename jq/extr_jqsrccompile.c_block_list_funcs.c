#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_4__ {scalar_t__ op; char* symbol; int /*<<< orphan*/  nformals; struct TYPE_4__* next; } ;
typedef  TYPE_1__ inst ;
struct TYPE_5__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;

/* Variables and functions */
 scalar_t__ CLOSURE_CREATE ; 
 scalar_t__ CLOSURE_CREATE_C ; 
 int /*<<< orphan*/  jv_keys_unsorted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,char*,int /*<<< orphan*/ ) ; 

jv block_list_funcs(block body, int omit_underscores) {
  jv funcs = jv_object(); // Use the keys for set semantics.
  for (inst *pos = body.first; pos != NULL; pos = pos->next) {
    if (pos->op == CLOSURE_CREATE || pos->op == CLOSURE_CREATE_C) {
      if (pos->symbol != NULL && (!omit_underscores || pos->symbol[0] != '_')) {
        funcs = jv_object_set(funcs, jv_string_fmt("%s/%i", pos->symbol, pos->nformals), jv_null());
      }
    }
  }
  return jv_keys_unsorted(funcs);
}