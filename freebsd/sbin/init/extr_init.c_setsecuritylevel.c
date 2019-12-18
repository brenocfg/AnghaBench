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
 int CTL_KERN ; 
 int KERN_SECURELVL ; 
 int /*<<< orphan*/  emergency (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int getsecuritylevel () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  warning (char*,int,int) ; 

__attribute__((used)) static void
setsecuritylevel(int newlevel)
{
#ifdef KERN_SECURELVL
	int name[2], curlevel;

	curlevel = getsecuritylevel();
	if (newlevel == curlevel)
		return;
	name[0] = CTL_KERN;
	name[1] = KERN_SECURELVL;
	if (sysctl(name, 2, NULL, NULL, &newlevel, sizeof newlevel) == -1) {
		emergency(
		    "cannot change kernel security level from %d to %d: %s",
		    curlevel, newlevel, strerror(errno));
		return;
	}
#ifdef SECURE
	warning("kernel security level changed from %d to %d",
	    curlevel, newlevel);
#endif
#endif
}