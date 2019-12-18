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
struct value {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  obase; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 struct value* pop () ; 
 int /*<<< orphan*/  print_value (int /*<<< orphan*/ ,struct value*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
pop_printn(void)
{
	struct value *value = pop();

	if (value != NULL) {
		print_value(stdout, value, "", bmachine.obase);
		fflush(stdout);
		stack_free_value(value);
	}
}