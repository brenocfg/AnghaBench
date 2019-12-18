#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {struct TYPE_4__* link; } ;
typedef  TYPE_1__ restrict_u ;

/* Variables and functions */
 int /*<<< orphan*/  send_restrict_entry (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
send_restrict_list(
	restrict_u *	pres,
	int		ipv6,
	u_int *		pidx
	)
{
	for ( ; pres != NULL; pres = pres->link) {
		send_restrict_entry(pres, ipv6, *pidx);
		(*pidx)++;
	}
}