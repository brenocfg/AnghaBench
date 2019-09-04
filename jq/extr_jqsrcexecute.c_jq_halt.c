#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* jv ;
struct TYPE_3__ {int halted; void* error_message; void* exit_code; } ;
typedef  TYPE_1__ jq_state ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
jq_halt(jq_state *jq, jv exit_code, jv error_message)
{
  assert(!jq->halted);
  jq->halted = 1;
  jq->exit_code = exit_code;
  jq->error_message = error_message;
}