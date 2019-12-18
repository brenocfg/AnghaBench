#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stack_t_ {scalar_t__ stack; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; } ;
struct sighand {scalar_t__ altstack; int /*<<< orphan*/  altstack_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  esp; } ;
struct TYPE_4__ {TYPE_1__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_DISABLE_ ; 
 int /*<<< orphan*/  SS_ONSTACK_ ; 
 TYPE_2__* current ; 
 scalar_t__ is_on_altstack (int /*<<< orphan*/ ,struct sighand*) ; 

__attribute__((used)) static void altstack_to_user(struct sighand *sighand, struct stack_t_ *user_stack) {
    user_stack->stack = sighand->altstack;
    user_stack->size = sighand->altstack_size;
    user_stack->flags = 0;
    if (sighand->altstack == 0)
        user_stack->flags |= SS_DISABLE_;
    if (is_on_altstack(current->cpu.esp, sighand))
        user_stack->flags |= SS_ONSTACK_;
}