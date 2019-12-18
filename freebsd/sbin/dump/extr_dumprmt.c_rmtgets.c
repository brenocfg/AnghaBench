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
 int /*<<< orphan*/  msg (char*,...) ; 
 int /*<<< orphan*/  rmtconnaborted (int /*<<< orphan*/ ) ; 
 char rmtgetb () ; 

void
rmtgets(char *line, int len)
{
	char *cp = line;

	while (len > 1) {
		*cp = rmtgetb();
		if (*cp == '\n') {
			cp[1] = '\0';
			return;
		}
		cp++;
		len--;
	}
	*cp = '\0';
	msg("Protocol to remote tape server botched.\n");
	msg("(rmtgets got \"%s\").\n", line);
	rmtconnaborted(0);
}