#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int /*<<< orphan*/  fd; struct TYPE_3__* next; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  BSIZE ; 
 int /*<<< orphan*/  DEFFILEMODE ; 
 int EXIT_FAILURE ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  add (int,char*) ; 
 scalar_t__ caph_enter () ; 
 int caph_limit_stderr () ; 
 int caph_limit_stdin () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 TYPE_1__* head ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
main(int argc, char *argv[])
{
	LIST *p;
	int n, fd, rval, wval;
	char *bp;
	int append, ch, exitval;
	char *buf;
#define	BSIZE (8 * 1024)

	append = 0;
	while ((ch = getopt(argc, argv, "ai")) != -1)
		switch((char)ch) {
		case 'a':
			append = 1;
			break;
		case 'i':
			(void)signal(SIGINT, SIG_IGN);
			break;
		case '?':
		default:
			usage();
		}
	argv += optind;
	argc -= optind;

	if ((buf = malloc(BSIZE)) == NULL)
		err(1, "malloc");

	if (caph_limit_stdin() == -1 || caph_limit_stderr() == -1)
		err(EXIT_FAILURE, "unable to limit stdio");

	add(STDOUT_FILENO, "stdout");

	for (exitval = 0; *argv; ++argv)
		if ((fd = open(*argv, append ? O_WRONLY|O_CREAT|O_APPEND :
		    O_WRONLY|O_CREAT|O_TRUNC, DEFFILEMODE)) < 0) {
			warn("%s", *argv);
			exitval = 1;
		} else
			add(fd, *argv);

	if (caph_enter() < 0)
		err(EXIT_FAILURE, "unable to enter capability mode");
	while ((rval = read(STDIN_FILENO, buf, BSIZE)) > 0)
		for (p = head; p; p = p->next) {
			n = rval;
			bp = buf;
			do {
				if ((wval = write(p->fd, bp, n)) == -1) {
					warn("%s", p->name);
					exitval = 1;
					break;
				}
				bp += wval;
			} while (n -= wval);
		}
	if (rval < 0)
		err(1, "read");
	exit(exitval);
}