#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_3__ {int e_c; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EVENT ;
typedef  int ARG_CHAR_T ;

/* Variables and functions */
 int EC_MAPCOMMAND ; 
 int EC_MAPNODIGIT ; 
 scalar_t__ GC_OK ; 
 scalar_t__ ISDIGIT (int) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ v_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int
v_count(
	SCR *sp,
	ARG_CHAR_T fkey,
	u_long *countp)
{
	EVENT ev;
	u_long count, tc;

	ev.e_c = fkey;
	count = tc = 0;
	do {
		/*
		 * XXX
		 * Assume that overflow results in a smaller number.
		 */
		tc = count * 10 + ev.e_c - '0';
		if (count > tc) {
			/* Toss to the next non-digit. */
			do {
				if (v_key(sp, 0, &ev,
				    EC_MAPCOMMAND | EC_MAPNODIGIT) != GC_OK)
					return (1);
			} while (ISDIGIT(ev.e_c));
			msgq(sp, M_ERR,
			    "235|Number larger than %lu", ULONG_MAX);
			return (1);
		}
		count = tc;
		if (v_key(sp, 0, &ev, EC_MAPCOMMAND | EC_MAPNODIGIT) != GC_OK)
			return (1);
	} while (ISDIGIT(ev.e_c));
	*countp = count;
	return (0);
}