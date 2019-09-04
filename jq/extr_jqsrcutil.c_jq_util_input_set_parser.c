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
typedef  int /*<<< orphan*/  jv_parser ;
struct TYPE_3__ {int /*<<< orphan*/  slurped; int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ jq_util_input_state ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

void jq_util_input_set_parser(jq_util_input_state *state, jv_parser *parser, int slurp) {
  assert(!jv_is_valid(state->slurped));
  state->parser = parser;

  if (parser == NULL && slurp)
    state->slurped = jv_string("");
  else if (slurp)
    state->slurped = jv_array();
  else
    state->slurped = jv_invalid();
}