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
struct ucred {int cr_ref; int /*<<< orphan*/  cr_loginclass; int /*<<< orphan*/  cr_prison; int /*<<< orphan*/  cr_ruidinfo; int /*<<< orphan*/  cr_uidinfo; int /*<<< orphan*/  cr_groups; int /*<<< orphan*/  cr_ngroups; int /*<<< orphan*/  cr_startcopy; int /*<<< orphan*/  cr_endcopy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  audit_cred_copy (struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  crsetgroups (struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loginclass_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_cred_copy (struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  prison_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uihold (int /*<<< orphan*/ ) ; 

void
crcopy(struct ucred *dest, struct ucred *src)
{

	KASSERT(dest->cr_ref == 1, ("crcopy of shared ucred"));
	bcopy(&src->cr_startcopy, &dest->cr_startcopy,
	    (unsigned)((caddr_t)&src->cr_endcopy -
		(caddr_t)&src->cr_startcopy));
	crsetgroups(dest, src->cr_ngroups, src->cr_groups);
	uihold(dest->cr_uidinfo);
	uihold(dest->cr_ruidinfo);
	prison_hold(dest->cr_prison);
	loginclass_hold(dest->cr_loginclass);
#ifdef AUDIT
	audit_cred_copy(src, dest);
#endif
#ifdef MAC
	mac_cred_copy(src, dest);
#endif
}