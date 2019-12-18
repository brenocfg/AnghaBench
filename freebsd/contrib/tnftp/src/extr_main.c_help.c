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
struct cmd {char* c_name; int /*<<< orphan*/  c_help; int /*<<< orphan*/  (* c_handler ) (int /*<<< orphan*/ ,char**) ;scalar_t__ c_proxy; } ;
typedef  int /*<<< orphan*/  cmdbuf ;
typedef  int /*<<< orphan*/  StringList ;

/* Variables and functions */
 char* HELPINDENT ; 
 int MAX_C_NAME ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 struct cmd* cmdtab ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  ftp_sl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ftp_sl_init () ; 
 int /*<<< orphan*/  ftp_strdup (char const*) ; 
 struct cmd* getcmd (char*) ; 
 int /*<<< orphan*/  list_vertical (int /*<<< orphan*/ *) ; 
 scalar_t__ proxy ; 
 int /*<<< orphan*/  sl_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ttyout ; 

void
help(int argc, char *argv[])
{
	struct cmd *c;
	char *nargv[1], *cmd;
	const char *p;
	int isusage;

	cmd = argv[0];
	isusage = (strcmp(cmd, "usage") == 0);
	if (argc == 0 || (isusage && argc == 1)) {
		UPRINTF("usage: %s [command [...]]\n", cmd);
		return;
	}
	if (argc == 1) {
		StringList *buf;

		buf = ftp_sl_init();
		fprintf(ttyout,
		    "%sommands may be abbreviated.  Commands are:\n\n",
		    proxy ? "Proxy c" : "C");
		for (c = cmdtab; (p = c->c_name) != NULL; c++)
			if (!proxy || c->c_proxy)
				ftp_sl_add(buf, ftp_strdup(p));
		list_vertical(buf);
		sl_free(buf, 1);
		return;
	}

#define	HELPINDENT ((int) sizeof("disconnect"))

	while (--argc > 0) {
		char *arg;
		char cmdbuf[MAX_C_NAME];

		arg = *++argv;
		c = getcmd(arg);
		if (c == (struct cmd *)-1)
			fprintf(ttyout, "?Ambiguous %s command `%s'\n",
			    cmd, arg);
		else if (c == NULL)
			fprintf(ttyout, "?Invalid %s command `%s'\n",
			    cmd, arg);
		else {
			if (isusage) {
				(void)strlcpy(cmdbuf, c->c_name, sizeof(cmdbuf));
				nargv[0] = cmdbuf;
				(*c->c_handler)(0, nargv);
			} else
				fprintf(ttyout, "%-*s\t%s\n", HELPINDENT,
				    c->c_name, c->c_help);
		}
	}
}