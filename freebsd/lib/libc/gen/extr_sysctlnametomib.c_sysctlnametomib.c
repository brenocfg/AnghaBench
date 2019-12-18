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
 int CTL_SYSCTL ; 
 int CTL_SYSCTL_NAME2OID ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int sysctl (int*,int,int*,size_t*,char const*,int /*<<< orphan*/ ) ; 

int
sysctlnametomib(const char *name, int *mibp, size_t *sizep)
{
	int oid[2];
	int error;

	oid[0] = CTL_SYSCTL;
	oid[1] = CTL_SYSCTL_NAME2OID;

	*sizep *= sizeof(int);
	error = sysctl(oid, 2, mibp, sizep, name, strlen(name));
	*sizep /= sizeof(int);
	return (error);
}