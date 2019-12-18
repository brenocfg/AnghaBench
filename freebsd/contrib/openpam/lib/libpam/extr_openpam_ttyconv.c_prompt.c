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
 int /*<<< orphan*/  O_RDWR ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpurge (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int prompt_notty (char const*,char*) ; 
 int prompt_tty (int,int,char const*,char*,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
prompt(const char *message, char *response, int echo)
{
	int ifd, ofd, ret;

	if (isatty(STDIN_FILENO)) {
		fflush(stdout);
#ifdef HAVE_FPURGE
		fpurge(stdin);
#endif
		ifd = STDIN_FILENO;
		ofd = STDOUT_FILENO;
	} else {
		if ((ifd = open("/dev/tty", O_RDWR)) < 0)
			/* no way to prevent echo */
			return (prompt_notty(message, response));
		ofd = ifd;
	}
	ret = prompt_tty(ifd, ofd, message, response, echo);
	if (ifd != STDIN_FILENO)
		close(ifd);
	return (ret);
}