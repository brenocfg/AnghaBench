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
typedef  int u_int ;
struct uidinfo {int /*<<< orphan*/  ui_sbsize; } ;
typedef  scalar_t__ rlim_t ;

/* Variables and functions */
 int chglimit (struct uidinfo*,int /*<<< orphan*/ *,int,scalar_t__,char*) ; 

int
chgsbsize(struct uidinfo *uip, u_int *hiwat, u_int to, rlim_t max)
{
	int diff, rv;

	diff = to - *hiwat;
	if (diff > 0 && max == 0) {
		rv = 0;
	} else {
		rv = chglimit(uip, &uip->ui_sbsize, diff, max, "sbsize");
		if (rv != 0)
			*hiwat = to;
	}
	return (rv);
}