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
struct interface {struct auth* int_auth; } ;
struct auth {scalar_t__ type; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int MAX_AUTH_KEYS ; 
 scalar_t__ RIP_AUTH_NONE ; 
 TYPE_1__ clk ; 

struct auth *
find_auth(struct interface *ifp)
{
	struct auth *ap, *res;
	int i;


	if (ifp == NULL)
		return 0;

	res = NULL;
	ap = ifp->int_auth;
	for (i = 0; i < MAX_AUTH_KEYS; i++, ap++) {
		/* stop looking after the last key */
		if (ap->type == RIP_AUTH_NONE)
			break;

		/* ignore keys that are not ready yet */
		if ((u_long)ap->start > (u_long)clk.tv_sec)
			continue;

		if ((u_long)ap->end < (u_long)clk.tv_sec) {
			/* note best expired password as a fall-back */
			if (res == NULL || (u_long)ap->end > (u_long)res->end)
				res = ap;
			continue;
		}

		/* note key with the best future */
		if (res == NULL || (u_long)res->end < (u_long)ap->end)
			res = ap;
	}
	return res;
}