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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  TESTFQDN ; 
 int /*<<< orphan*/  errno ; 
 size_t strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

int
gethostname(char *name, size_t namelen)
{
	if (strlcpy(name, TESTFQDN, namelen) > namelen) {
		errno = ENAMETOOLONG;
		return (-1);
	}
	return (0);
}