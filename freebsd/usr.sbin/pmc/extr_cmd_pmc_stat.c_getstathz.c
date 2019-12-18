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
struct clockinfo {int stathz; } ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_CLOCKRATE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int sysctl (int*,int,struct clockinfo*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getstathz(void)
{
	int mib[2];
	size_t size;
	struct clockinfo clockrate;

	mib[0] = CTL_KERN;
	mib[1] = KERN_CLOCKRATE;
	size = sizeof clockrate;
	if (sysctl(mib, 2, &clockrate, &size, NULL, 0) == -1)
		err(1, "sysctl kern.clockrate");
	return clockrate.stathz;
}