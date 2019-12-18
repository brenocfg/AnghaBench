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
 int /*<<< orphan*/  docmd (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ interactive ; 
 char* ntp_readline (int*) ; 
 int /*<<< orphan*/  ntp_readline_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntp_readline_uninit () ; 
 int /*<<< orphan*/ * prompt ; 

__attribute__((used)) static void
getcmds(void)
{
	char *	line;
	int	count;

	ntp_readline_init(interactive ? prompt : NULL);

	for (;;) {
		line = ntp_readline(&count);
		if (NULL == line)
			break;
		docmd(line);
		free(line);
	}

	ntp_readline_uninit();
}