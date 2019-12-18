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
typedef  scalar_t__ u_int ;
struct number {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {scalar_t__ scale; } ;

/* Variables and functions */
 scalar_t__ BN_is_negative (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ ULONG_MAX ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 scalar_t__ get_ulong (struct number*) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
set_scale(void)
{
	struct number *n;
	u_long scale;

	n = pop_number();
	if (n != NULL) {
		if (BN_is_negative(n->number))
			warnx("scale must be a nonnegative number");
		else {
			scale = get_ulong(n);
			if (scale != ULONG_MAX && scale <= UINT_MAX)
				bmachine.scale = (u_int)scale;
			else
				warnx("scale too large");
			}
		free_number(n);
	}
}