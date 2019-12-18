#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  call_identifier; } ;
struct TYPE_8__ {scalar_t__ next_state; TYPE_1__ extra; } ;
typedef  TYPE_2__ cmdp_token ;
typedef  scalar_t__ cmdp_state ;
struct TYPE_10__ {int /*<<< orphan*/  json_gen; } ;
struct TYPE_9__ {scalar_t__ next_state; int /*<<< orphan*/  json_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERATED_call (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ INITIAL ; 
 scalar_t__ __CALL ; 
 int /*<<< orphan*/  clear_stack () ; 
 TYPE_5__ command_output ; 
 scalar_t__ state ; 
 scalar_t__* statelist ; 
 int statelist_idx ; 
 TYPE_3__ subcommand_output ; 

__attribute__((used)) static void next_state(const cmdp_token *token) {
    cmdp_state _next_state = token->next_state;

    //printf("token = name %s identifier %s\n", token->name, token->identifier);
    //printf("next_state = %d\n", token->next_state);
    if (token->next_state == __CALL) {
        subcommand_output.json_gen = command_output.json_gen;
        GENERATED_call(token->extra.call_identifier, &subcommand_output);
        _next_state = subcommand_output.next_state;
        clear_stack();
    }

    state = _next_state;
    if (state == INITIAL) {
        clear_stack();
    }

    /* See if we are jumping back to a state in which we were in previously
     * (statelist contains INITIAL) and just move statelist_idx accordingly. */
    for (int i = 0; i < statelist_idx; i++) {
        if (statelist[i] != _next_state)
            continue;
        statelist_idx = i + 1;
        return;
    }

    /* Otherwise, the state is new and we add it to the list */
    statelist[statelist_idx++] = _next_state;
}