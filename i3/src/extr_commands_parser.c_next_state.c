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
struct TYPE_10__ {int needs_tree_render; int /*<<< orphan*/  client; int /*<<< orphan*/  json_gen; } ;
struct TYPE_9__ {int needs_tree_render; scalar_t__ next_state; int /*<<< orphan*/  client; int /*<<< orphan*/  json_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERATED_call (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ INITIAL ; 
 scalar_t__ __CALL ; 
 int /*<<< orphan*/  clear_stack () ; 
 TYPE_5__ command_output ; 
 scalar_t__ state ; 
 TYPE_3__ subcommand_output ; 

__attribute__((used)) static void next_state(const cmdp_token *token) {
    if (token->next_state == __CALL) {
        subcommand_output.json_gen = command_output.json_gen;
        subcommand_output.client = command_output.client;
        subcommand_output.needs_tree_render = false;
        GENERATED_call(token->extra.call_identifier, &subcommand_output);
        state = subcommand_output.next_state;
        /* If any subcommand requires a tree_render(), we need to make the
         * whole parser result request a tree_render(). */
        if (subcommand_output.needs_tree_render)
            command_output.needs_tree_render = true;
        clear_stack();
        return;
    }

    state = token->next_state;
    if (state == INITIAL) {
        clear_stack();
    }
}