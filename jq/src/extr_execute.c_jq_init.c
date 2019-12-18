#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * nomem_handler_data; int /*<<< orphan*/ * nomem_handler; void* value_at_path; void* path; int /*<<< orphan*/  attrs; int /*<<< orphan*/  err_cb_data; int /*<<< orphan*/  err_cb; void* error_message; void* exit_code; scalar_t__ halted; void* error; scalar_t__ curr_frame; scalar_t__ fork_top; scalar_t__ stk_top; int /*<<< orphan*/  stk; scalar_t__ next_label; scalar_t__ bc; } ;
typedef  TYPE_1__ jq_state ;

/* Variables and functions */
 int /*<<< orphan*/  default_err_cb ; 
 void* jv_invalid () ; 
 TYPE_1__* jv_mem_alloc_unguarded (int) ; 
 void* jv_null () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  stack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

jq_state *jq_init(void) {
  jq_state *jq;
  jq = jv_mem_alloc_unguarded(sizeof(*jq));
  if (jq == NULL)
    return NULL;

  jq->bc = 0;
  jq->next_label = 0;

  stack_init(&jq->stk);
  jq->stk_top = 0;
  jq->fork_top = 0;
  jq->curr_frame = 0;
  jq->error = jv_null();

  jq->halted = 0;
  jq->exit_code = jv_invalid();
  jq->error_message = jv_invalid();

  jq->err_cb = default_err_cb;
  jq->err_cb_data = stderr;

  jq->attrs = jv_object();
  jq->path = jv_null();
  jq->value_at_path = jv_null();

  jq->nomem_handler = NULL;
  jq->nomem_handler_data = NULL;
  return jq;
}