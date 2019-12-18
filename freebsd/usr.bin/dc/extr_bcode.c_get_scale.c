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
struct TYPE_2__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 

__attribute__((used)) static void
get_scale(void)
{
	struct number *n;

	n = new_number();
	bn_check(BN_set_word(n->number, bmachine.scale));
	push_number(n);
}