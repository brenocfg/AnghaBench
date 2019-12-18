#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct number {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 size_t stack_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stackdepth(void)
{
	struct number *n;
	size_t i;

	i = stack_size(&bmachine.stack);
	n = new_number();
	bn_check(BN_set_word(n->number, i));
	push_number(n);
}