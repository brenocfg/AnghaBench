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
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int strtonum (char const*,int,int,char const**) ; 
 int sys_nsig ; 
 int /*<<< orphan*/ * sys_signame ; 

__attribute__((used)) static int
parse_signal(const char *str)
{
	int sig, i;
	const char *errstr;

	sig = strtonum(str, 1, sys_nsig - 1, &errstr);

	if (errstr == NULL)
		return (sig);
	if (strncasecmp(str, "SIG", 3) == 0)
		str += 3;

	for (i = 1; i < sys_nsig; i++) {
		if (strcasecmp(str, sys_signame[i]) == 0)
			return (i);
	}

	errx(125, "invalid signal");
}