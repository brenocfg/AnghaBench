#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct frame {scalar_t__ retaddr; scalar_t__ retdata; } ;
struct closure {int member_1; TYPE_1__* member_0; } ;
typedef  int /*<<< orphan*/  jv ;
struct TYPE_10__ {int debug_trace_enabled; int initial_execution; TYPE_1__* bc; int /*<<< orphan*/  nomem_handler_data; int /*<<< orphan*/  nomem_handler; } ;
typedef  TYPE_2__ jq_state ;
struct TYPE_9__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int JQ_DEBUG_TRACE_ALL ; 
 struct frame* frame_push (TYPE_2__*,struct closure,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  jv_nomem_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_get_pos (TYPE_2__*) ; 
 int /*<<< orphan*/  stack_push (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_save (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void jq_start(jq_state *jq, jv input, int flags) {
  jv_nomem_handler(jq->nomem_handler, jq->nomem_handler_data);
  jq_reset(jq);

  struct closure top = {jq->bc, -1};
  struct frame* top_frame = frame_push(jq, top, 0, 0);
  top_frame->retdata = 0;
  top_frame->retaddr = 0;

  stack_push(jq, input);
  stack_save(jq, jq->bc->code, stack_get_pos(jq));
  jq->debug_trace_enabled = flags & JQ_DEBUG_TRACE_ALL;
  jq->initial_execution = 1;
}