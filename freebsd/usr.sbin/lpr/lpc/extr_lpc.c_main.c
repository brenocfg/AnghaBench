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
struct cmd {int c_opts; int /*<<< orphan*/  (* c_handler ) (int,char**) ;int /*<<< orphan*/ * c_generic; } ;
typedef  char* PRIV_END ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_LPR ; 
 int LPC_PRIVCMD ; 
 int /*<<< orphan*/  LPR_OPER ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  cmdscanner () ; 
 int /*<<< orphan*/  euid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fromatty ; 
 int /*<<< orphan*/  generic (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (int,char**),int,char**) ; 
 struct cmd* getcmd (char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 scalar_t__ getuid () ; 
 scalar_t__ ingroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 scalar_t__ uid ; 

int
main(int argc, char *argv[])
{
	register struct cmd *c;

	euid = geteuid();
	uid = getuid();
	PRIV_END
	progname = argv[0];
	openlog("lpd", 0, LOG_LPR);

	if (--argc > 0) {
		c = getcmd(*++argv);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			exit(1);
		}
		if (c == NULL) {
			printf("?Invalid command\n");
			exit(1);
		}
		if ((c->c_opts & LPC_PRIVCMD) && getuid() &&
		    ingroup(LPR_OPER) == 0) {
			printf("?Privileged command\n");
			exit(1);
		}
		if (c->c_generic != NULL)
			generic(c->c_generic, c->c_opts, c->c_handler,
			    argc, argv);
		else
			(*c->c_handler)(argc, argv);
		exit(0);
	}
	fromatty = isatty(fileno(stdin));
	if (!fromatty)
		signal(SIGINT, intr);
	for (;;) {
		cmdscanner();
	}
}