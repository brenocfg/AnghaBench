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
typedef  scalar_t__ u_long ;
struct number {int dummy; } ;
struct TYPE_2__ {scalar_t__ readsp; } ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 scalar_t__ get_ulong (struct number*) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  src_free () ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
quitN(void)
{
	struct number *n;
	u_long i;

	n = pop_number();
	if (n == NULL)
		return;
	i = get_ulong(n);
	free_number(n);
	if (i == ULONG_MAX || i == 0)
		warnx("Q command requires a number >= 1");
	else if (bmachine.readsp < i)
		warnx("Q command argument exceeded string execution depth");
	else {
		while (i-- > 0) {
			src_free();
			bmachine.readsp--;
		}
	}
}