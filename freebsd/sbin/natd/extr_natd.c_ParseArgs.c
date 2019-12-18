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
typedef  int /*<<< orphan*/  parmBuf ;

/* Variables and functions */
 int /*<<< orphan*/  ParseOption (char*,char*) ; 
 int /*<<< orphan*/  Usage () ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void ParseArgs (int argc, char** argv)
{
	int		arg;
	char*		opt;
	char		parmBuf[256];
	int		len; /* bounds checking */

	for (arg = 1; arg < argc; arg++) {

		opt  = argv[arg];
		if (*opt != '-') {

			warnx ("invalid option %s", opt);
			Usage ();
		}

		parmBuf[0] = '\0';
		len = 0;

		while (arg < argc - 1) {

			if (argv[arg + 1][0] == '-')
				break;

			if (len) {
				strncat (parmBuf, " ", sizeof(parmBuf) - (len + 1));
				len += strlen(parmBuf + len);
			}

			++arg;
			strncat (parmBuf, argv[arg], sizeof(parmBuf) - (len + 1));
			len += strlen(parmBuf + len);

		}

		ParseOption (opt + 1, (len ? parmBuf : NULL));

	}
}