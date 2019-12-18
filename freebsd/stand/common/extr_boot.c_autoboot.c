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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int autoboot_tried ; 
 int command_boot (int,char**) ; 
 char* command_errmsg ; 
 int getchar () ; 
 char* getenv (char*) ; 
 scalar_t__ ischar () ; 
 int /*<<< orphan*/  loadakernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
autoboot(int timeout, char *prompt)
{
	time_t	when, otime, ntime;
	int		c, yes;
	char	*argv[2], *cp, *ep;
	char	*kernelname;
#ifdef BOOT_PROMPT_123
	const char	*seq = "123", *p = seq;
#endif

	autoboot_tried = 1;

	if (timeout == -1) {
		timeout = 10;
		/* try to get a delay from the environment */
		if ((cp = getenv("autoboot_delay"))) {
			timeout = strtol(cp, &ep, 0);
			if (cp == ep)
				timeout = 10;		/* Unparseable? Set default! */
		}
	}

	kernelname = getenv("kernelname");
	if (kernelname == NULL) {
		argv[0] = NULL;
		loadakernel(0, 0, argv);
		kernelname = getenv("kernelname");
		if (kernelname == NULL) {
			command_errmsg = "no valid kernel found";
			return(CMD_ERROR);
		}
	}

	if (timeout >= 0) {
		otime = time(NULL);
		when = otime + timeout;	/* when to boot */

		yes = 0;

#ifdef BOOT_PROMPT_123
		printf("%s\n", (prompt == NULL) ? "Hit [Enter] to boot immediately, or "
		    "1 2 3 sequence for command prompt." : prompt);
#else
		printf("%s\n", (prompt == NULL) ? "Hit [Enter] to boot immediately, or any other key for command prompt." : prompt);
#endif

		for (;;) {
			if (ischar()) {
				c = getchar();
#ifdef BOOT_PROMPT_123
				if ((c == '\r') || (c == '\n')) {
					yes = 1;
					break;
				} else if (c != *p++)
					p = seq;
				if (*p == 0)
					break;
#else
				if ((c == '\r') || (c == '\n'))
					yes = 1;
				break;
#endif
			}
			ntime = time(NULL);
			if (ntime >= when) {
				yes = 1;
				break;
			}

			if (ntime != otime) {
				printf("\rBooting [%s] in %d second%s... ",
				    kernelname, (int)(when - ntime),
				    (when-ntime)==1?"":"s");
				otime = ntime;
			}
		}
	} else {
		yes = 1;
	}

	if (yes)
		printf("\rBooting [%s]...               ", kernelname);
	putchar('\n');
	if (yes) {
		argv[0] = "boot";
		argv[1] = NULL;
		return(command_boot(1, argv));
	}
	return(CMD_OK);
}