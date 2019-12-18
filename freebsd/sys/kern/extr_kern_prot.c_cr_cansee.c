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
struct ucred {int dummy; } ;

/* Variables and functions */
 int cr_canseejailproc (struct ucred*,struct ucred*) ; 
 int cr_canseeothergids (struct ucred*,struct ucred*) ; 
 int cr_canseeotheruids (struct ucred*,struct ucred*) ; 
 int mac_cred_check_visible (struct ucred*,struct ucred*) ; 
 int prison_check (struct ucred*,struct ucred*) ; 

int
cr_cansee(struct ucred *u1, struct ucred *u2)
{
	int error;

	if ((error = prison_check(u1, u2)))
		return (error);
#ifdef MAC
	if ((error = mac_cred_check_visible(u1, u2)))
		return (error);
#endif
	if ((error = cr_canseeotheruids(u1, u2)))
		return (error);
	if ((error = cr_canseeothergids(u1, u2)))
		return (error);
	if ((error = cr_canseejailproc(u1, u2)))
		return (error);
	return (0);
}