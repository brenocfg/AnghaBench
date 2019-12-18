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
struct number {scalar_t__ scale; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,scalar_t__) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 

__attribute__((used)) static void
badd(void)
{
	struct number	*a, *b, *r;

	a = pop_number();
	if (a == NULL)
		return;
	b = pop_number();
	if (b == NULL) {
		push_number(a);
		return;
	}

	r = new_number();
	r->scale = max(a->scale, b->scale);
	if (r->scale > a->scale)
		normalize(a, r->scale);
	else if (r->scale > b->scale)
		normalize(b, r->scale);
	bn_check(BN_add(r->number, a->number, b->number));
	push_number(r);
	free_number(a);
	free_number(b);
}