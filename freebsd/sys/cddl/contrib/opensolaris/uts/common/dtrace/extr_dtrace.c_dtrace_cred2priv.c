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
typedef  int /*<<< orphan*/  zoneid_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int DTRACE_PRIV_ALL ; 
 int DTRACE_PRIV_KERNEL ; 
 int DTRACE_PRIV_OWNER ; 
 int DTRACE_PRIV_PROC ; 
 int DTRACE_PRIV_USER ; 
 int DTRACE_PRIV_ZONEOWNER ; 
 int /*<<< orphan*/  PRIV_ALL ; 
 int /*<<< orphan*/  PRIV_DTRACE_KERNEL ; 
 int /*<<< orphan*/  PRIV_DTRACE_PROC ; 
 int /*<<< orphan*/  PRIV_DTRACE_USER ; 
 scalar_t__ PRIV_POLICY_ONLY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_PROC_OWNER ; 
 int /*<<< orphan*/  PRIV_PROC_ZONE ; 
 int /*<<< orphan*/  crgetuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crgetzoneid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_cred2priv(cred_t *cr, uint32_t *privp, uid_t *uidp, zoneid_t *zoneidp)
{
	uint32_t priv;

#ifdef illumos
	if (cr == NULL || PRIV_POLICY_ONLY(cr, PRIV_ALL, B_FALSE)) {
		/*
		 * For DTRACE_PRIV_ALL, the uid and zoneid don't matter.
		 */
		priv = DTRACE_PRIV_ALL;
	} else {
		*uidp = crgetuid(cr);
		*zoneidp = crgetzoneid(cr);

		priv = 0;
		if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_KERNEL, B_FALSE))
			priv |= DTRACE_PRIV_KERNEL | DTRACE_PRIV_USER;
		else if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_USER, B_FALSE))
			priv |= DTRACE_PRIV_USER;
		if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_PROC, B_FALSE))
			priv |= DTRACE_PRIV_PROC;
		if (PRIV_POLICY_ONLY(cr, PRIV_PROC_OWNER, B_FALSE))
			priv |= DTRACE_PRIV_OWNER;
		if (PRIV_POLICY_ONLY(cr, PRIV_PROC_ZONE, B_FALSE))
			priv |= DTRACE_PRIV_ZONEOWNER;
	}
#else
	priv = DTRACE_PRIV_ALL;
#endif

	*privp = priv;
}