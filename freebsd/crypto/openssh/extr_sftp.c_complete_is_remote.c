#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int t; scalar_t__ c; } ;

/* Variables and functions */
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncasecmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
complete_is_remote(char *cmd) {
	int i;

	if (cmd == NULL)
		return -1;

	for (i = 0; cmds[i].c; i++) {
		if (!strncasecmp(cmd, cmds[i].c, strlen(cmds[i].c)))
			return cmds[i].t;
	}

	return -1;
}