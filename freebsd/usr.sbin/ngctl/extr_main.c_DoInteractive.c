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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ CMDRTN_QUIT ; 
 scalar_t__ DoParseCommand (char*) ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int LINE_MAX ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* PROMPT ; 
 int /*<<< orphan*/  ReadSockets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  dsock ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ help_cmd ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ select (int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DoInteractive(void)
{
	const int maxfd = MAX(csock, dsock) + 1;

	(*help_cmd.func)(0, NULL);
	while (1) {
		struct timeval tv;
		fd_set rfds;

		/* See if any data or control messages are arriving */
		FD_ZERO(&rfds);
		FD_SET(csock, &rfds);
		FD_SET(dsock, &rfds);
		memset(&tv, 0, sizeof(tv));
		if (select(maxfd, &rfds, NULL, NULL, &tv) <= 0) {

			/* Issue prompt and wait for anything to happen */
			printf("%s", PROMPT);
			fflush(stdout);
			FD_ZERO(&rfds);
			FD_SET(0, &rfds);
			FD_SET(csock, &rfds);
			FD_SET(dsock, &rfds);
			if (select(maxfd, &rfds, NULL, NULL, NULL) < 0)
				err(EX_OSERR, "select");

			/* If not user input, print a newline first */
			if (!FD_ISSET(0, &rfds))
				printf("\n");
		}

		ReadSockets(&rfds);

		/* Get any user input */
		if (FD_ISSET(0, &rfds)) {
			char buf[LINE_MAX];

			if (fgets(buf, sizeof(buf), stdin) == NULL) {
				printf("\n");
				break;
			}
			if (DoParseCommand(buf) == CMDRTN_QUIT)
				break;
		}
	}
	return (CMDRTN_QUIT);
}