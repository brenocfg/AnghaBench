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
struct termios {int /*<<< orphan*/  c_lflag; } ;
struct group {char* gr_passwd; char* gr_name; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  TCSANOW ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int isatty (int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* pw_pwcrypt (char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strchr (char*,char) ; 
 char* strpbrk (char*,char*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
grp_set_passwd(struct group *grp, bool update, int fd, bool precrypted)
{
	int		 b;
	int		 istty;
	struct termios	 t, n;
	char		*p, line[256];

	if (fd == -1)
		return;

	if (fd == '-') {
		grp->gr_passwd = "*";	/* No access */
		return;
	}
	
	if ((istty = isatty(fd))) {
		n = t;
		/* Disable echo */
		n.c_lflag &= ~(ECHO);
		tcsetattr(fd, TCSANOW, &n);
		printf("%sassword for group %s:", update ? "New p" : "P",
		    grp->gr_name);
		fflush(stdout);
	}
	b = read(fd, line, sizeof(line) - 1);
	if (istty) {	/* Restore state */
		tcsetattr(fd, TCSANOW, &t);
		fputc('\n', stdout);
		fflush(stdout);
	}
	if (b < 0)
		err(EX_OSERR, "-h file descriptor");
	line[b] = '\0';
	if ((p = strpbrk(line, " \t\r\n")) != NULL)
		*p = '\0';
	if (!*line)
		errx(EX_DATAERR, "empty password read on file descriptor %d",
		    conf.fd);
	if (precrypted) {
		if (strchr(line, ':') != 0)
			errx(EX_DATAERR, "wrong encrypted passwrd");
		grp->gr_passwd = line;
	} else
		grp->gr_passwd = pw_pwcrypt(line);
}