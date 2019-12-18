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
struct cmd {int /*<<< orphan*/  (* c_handler ) (int,char**) ;int /*<<< orphan*/  c_name; scalar_t__ c_conn; int /*<<< orphan*/  c_proxy; } ;
typedef  int /*<<< orphan*/  sigfunc ;
typedef  int /*<<< orphan*/  cmdbuf ;

/* Variables and functions */
 int MAX_C_NAME ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  abortprox ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 struct cmd* getcmd (char*) ; 
 scalar_t__ line ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  proxabort ; 
 int proxflag ; 
 int /*<<< orphan*/  pswitch (int) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int strcspn (scalar_t__,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
doproxy(int argc, char *argv[])
{
	struct cmd *c;
	int cmdpos;
	sigfunc oldintr;
	char cmdbuf[MAX_C_NAME];

	if (argc == 0 || (argc == 1 && !another(&argc, &argv, "command"))) {
		UPRINTF("usage: %s command\n", argv[0]);
		code = -1;
		return;
	}
	c = getcmd(argv[1]);
	if (c == (struct cmd *) -1) {
		fputs("?Ambiguous command.\n", ttyout);
		code = -1;
		return;
	}
	if (c == 0) {
		fputs("?Invalid command.\n", ttyout);
		code = -1;
		return;
	}
	if (!c->c_proxy) {
		fputs("?Invalid proxy command.\n", ttyout);
		code = -1;
		return;
	}
	if (sigsetjmp(abortprox, 1)) {
		code = -1;
		return;
	}
	oldintr = xsignal(SIGINT, proxabort);
	pswitch(1);
	if (c->c_conn && !connected) {
		fputs("Not connected.\n", ttyout);
		pswitch(0);
		(void)xsignal(SIGINT, oldintr);
		code = -1;
		return;
	}
	cmdpos = strcspn(line, " \t");
	if (cmdpos > 0)		/* remove leading "proxy " from input buffer */
		memmove(line, line + cmdpos + 1, strlen(line) - cmdpos + 1);
	(void)strlcpy(cmdbuf, c->c_name, sizeof(cmdbuf));
	argv[1] = cmdbuf;
	(*c->c_handler)(argc-1, argv+1);
	if (connected) {
		proxflag = 1;
	}
	else {
		proxflag = 0;
	}
	pswitch(0);
	(void)xsignal(SIGINT, oldintr);
}