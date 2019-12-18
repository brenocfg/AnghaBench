#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct number {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCODE_LESS ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 scalar_t__ compare_numbers (int /*<<< orphan*/ ,struct number*,struct number*) ; 
 struct number* new_number () ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 

__attribute__((used)) static void
less_numbers(void)
{
	struct number *a, *b, *r;

	a = pop_number();
	if (a == NULL)
		return;
	b = pop_number();
	if (b == NULL) {
		push_number(a);
		return;
	}
	r = new_number();
	bn_check(BN_set_word(r->number,
	    compare_numbers(BCODE_LESS, a, b) ? 1 : 0));
	push_number(r);
}