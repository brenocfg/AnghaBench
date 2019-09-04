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
 int /*<<< orphan*/  ALLOC_ARRAY (char const**,int) ; 
 int /*<<< orphan*/  ALLOC_GROW (char const**,int,int) ; 
 int /*<<< orphan*/  FREE_AND_NULL (char const**) ; 
 int SPLIT_CMDLINE_BAD_ENDING ; 
 int SPLIT_CMDLINE_UNCLOSED_QUOTE ; 
 scalar_t__ isspace (char) ; 

int split_cmdline(char *cmdline, const char ***argv)
{
	int src, dst, count = 0, size = 16;
	char quoted = 0;

	ALLOC_ARRAY(*argv, size);

	/* split alias_string */
	(*argv)[count++] = cmdline;
	for (src = dst = 0; cmdline[src];) {
		char c = cmdline[src];
		if (!quoted && isspace(c)) {
			cmdline[dst++] = 0;
			while (cmdline[++src]
					&& isspace(cmdline[src]))
				; /* skip */
			ALLOC_GROW(*argv, count + 1, size);
			(*argv)[count++] = cmdline + dst;
		} else if (!quoted && (c == '\'' || c == '"')) {
			quoted = c;
			src++;
		} else if (c == quoted) {
			quoted = 0;
			src++;
		} else {
			if (c == '\\' && quoted != '\'') {
				src++;
				c = cmdline[src];
				if (!c) {
					FREE_AND_NULL(*argv);
					return -SPLIT_CMDLINE_BAD_ENDING;
				}
			}
			cmdline[dst++] = c;
			src++;
		}
	}

	cmdline[dst] = 0;

	if (quoted) {
		FREE_AND_NULL(*argv);
		return -SPLIT_CMDLINE_UNCLOSED_QUOTE;
	}

	ALLOC_GROW(*argv, count + 1, size);
	(*argv)[count] = NULL;

	return count;
}