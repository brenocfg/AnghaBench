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
struct sysctl_oid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSCTL_WLOCK () ; 
 int /*<<< orphan*/  SYSCTL_WUNLOCK () ; 
 int sysctl_remove_oid_locked (struct sysctl_oid*,int,int) ; 

int
sysctl_remove_oid(struct sysctl_oid *oidp, int del, int recurse)
{
	int error;

	SYSCTL_WLOCK();
	error = sysctl_remove_oid_locked(oidp, del, recurse);
	SYSCTL_WUNLOCK();
	return (error);
}