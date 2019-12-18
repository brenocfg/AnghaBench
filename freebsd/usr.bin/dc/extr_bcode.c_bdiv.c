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
struct number {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 
 struct number* div_number (struct number*,struct number*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 

__attribute__((used)) static void
bdiv(void)
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

	r = div_number(b, a, bmachine.scale);

	push_number(r);
	free_number(a);
	free_number(b);
}