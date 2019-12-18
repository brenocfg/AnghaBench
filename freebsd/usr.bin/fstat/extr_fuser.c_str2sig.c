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
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 int sys_nsig ; 
 int /*<<< orphan*/ * sys_signame ; 

__attribute__((used)) static int
str2sig(const char *str)
{
	int i;

	if (!strncasecmp(str, "SIG", 3))
		str += 3;
	for (i = 1; i < sys_nsig; i++) {
                if (!strcasecmp(sys_signame[i], str))
                        return (i);
        }
        return (-1);
}