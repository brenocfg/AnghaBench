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

/* Variables and functions */
 int ADE_AUDITON ; 
 int ADE_NOERR ; 
 int ADE_PARSE ; 
 int AUDIT_CNT ; 
 int POL_STR_SIZE ; 
 scalar_t__ au_strtopol (char*,int*) ; 
 scalar_t__ audit_set_policy (int*) ; 
 scalar_t__ getacpol (char*,int) ; 

int
auditd_set_policy(void)
{
	int policy;
	char polstr[POL_STR_SIZE];

	if (getacpol(polstr, POL_STR_SIZE) != 0 ||
	    au_strtopol(polstr, &policy) != 0) {
		policy = AUDIT_CNT;
		if (audit_set_policy(&policy) != 0)
			return (ADE_AUDITON);
		return (ADE_PARSE);
	}

	if (audit_set_policy(&policy) != 0)
		return (ADE_AUDITON);

	return (ADE_NOERR);
}