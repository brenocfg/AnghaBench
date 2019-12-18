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
struct ucred {scalar_t__ cr_uid; scalar_t__ cr_prison; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  see_jail_proc ; 

int
cr_canseejailproc(struct ucred *u1, struct ucred *u2)
{
	if (u1->cr_uid == 0)
		return (0);
	return (!see_jail_proc && u1->cr_prison != u2->cr_prison ? ESRCH : 0);
}