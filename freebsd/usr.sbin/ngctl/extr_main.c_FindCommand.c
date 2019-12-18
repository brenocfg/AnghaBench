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
struct ngcmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ MatchCommand (struct ngcmd const*,char const*) ; 
 struct ngcmd const** cmds ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static const struct ngcmd *
FindCommand(const char *string)
{
	int k, found = -1;

	for (k = 0; cmds[k] != NULL; k++) {
		if (MatchCommand(cmds[k], string)) {
			if (found != -1) {
				warnx("\"%s\": ambiguous command", string);
				return (NULL);
			}
			found = k;
		}
	}
	if (found == -1) {
		warnx("\"%s\": unknown command", string);
		return (NULL);
	}
	return (cmds[found]);
}