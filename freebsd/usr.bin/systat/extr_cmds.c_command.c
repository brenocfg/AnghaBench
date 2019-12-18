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
struct cmdtab {int c_flags; int /*<<< orphan*/  (* c_cmd ) (char*,char*) ;scalar_t__ (* c_init ) () ;int /*<<< orphan*/ * (* c_open ) () ;int /*<<< orphan*/  (* c_close ) (int /*<<< orphan*/ *) ;scalar_t__ c_name; } ;

/* Variables and functions */
 int CF_INIT ; 
 int /*<<< orphan*/  CMDLINE ; 
 int COLS ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  addch (char) ; 
 int /*<<< orphan*/  addstr (scalar_t__) ; 
 int /*<<< orphan*/  clrtoeol () ; 
 struct cmdtab* cmdtab ; 
 struct cmdtab* curcmd ; 
 unsigned int delay ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  labels () ; 
 int /*<<< orphan*/  load () ; 
 struct cmdtab* lookup (char*) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvaddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  status () ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (scalar_t__) ; 
 double strtod (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 () ; 
 int /*<<< orphan*/ * stub3 () ; 
 scalar_t__ stub4 () ; 
 int /*<<< orphan*/  stub5 (char*,char*) ; 
 int /*<<< orphan*/ * wnd ; 

void
command(const char *cmd)
{
	struct cmdtab *p;
	char *cp, *tmpstr, *tmpstr1;
	double t;

	tmpstr = tmpstr1 = strdup(cmd);
	for (cp = tmpstr1; *cp && !isspace(*cp); cp++)
		;
	if (*cp)
		*cp++ = '\0';
	if (*tmpstr1 == '\0')
		goto done;
	for (; *cp && isspace(*cp); cp++)
		;
	if (strcmp(tmpstr1, "quit") == 0 || strcmp(tmpstr1, "q") == 0)
		die(0);
	if (strcmp(tmpstr1, "load") == 0) {
		load();
		goto done;
	}
	if (strcmp(tmpstr1, "stop") == 0) {
		delay = 0;
		mvaddstr(CMDLINE, 0, "Refresh disabled.");
		clrtoeol();
		goto done;
	}
	if (strcmp(tmpstr1, "help") == 0) {
		int _col, _len;

		move(CMDLINE, _col = 0);
		for (p = cmdtab; p->c_name; p++) {
			_len = strlen(p->c_name);
			if (_col + _len > COLS)
				break;
			addstr(p->c_name); _col += _len;
			if (_col + 1 < COLS)
				addch(' ');
		}
		clrtoeol();
		goto done;
	}
	t = strtod(tmpstr1, NULL) * 1000000.0;
	if (t > 0 && t < (double)UINT_MAX)
		delay = (unsigned int)t;
	if ((t <= 0 || t > (double)UINT_MAX) &&
	    (strcmp(tmpstr1, "start") == 0 ||
	    strcmp(tmpstr1, "interval") == 0)) {
		if (*cp != '\0') {
			t = strtod(cp, NULL) * 1000000.0;
			if (t <= 0 || t >= (double)UINT_MAX) {
				error("%d: bad interval.", (int)t);
				goto done;
			}
		}
	}
	if (t > 0) {
		delay = (unsigned int)t;
		display();
		status();
		goto done;
	}
	p = lookup(tmpstr1);
	if (p == (struct cmdtab *)-1) {
		error("%s: Ambiguous command.", tmpstr1);
		goto done;
	}
	if (p) {
		if (curcmd == p)
			goto done;
		(*curcmd->c_close)(wnd);
		curcmd->c_flags &= ~CF_INIT;
		wnd = (*p->c_open)();
		if (wnd == NULL) {
			error("Couldn't open new display");
			wnd = (*curcmd->c_open)();
			if (wnd == NULL) {
				error("Couldn't change back to previous cmd");
				exit(1);
			}
			p = curcmd;
		}
		if ((p->c_flags & CF_INIT) == 0) {
			if ((*p->c_init)())
				p->c_flags |= CF_INIT;
			else
				goto done;
		}
		curcmd = p;
		labels();
		display();
		status();
		goto done;
	}
	if (curcmd->c_cmd == NULL || !(*curcmd->c_cmd)(tmpstr1, cp))
		error("%s: Unknown command.", tmpstr1);
done:
	free(tmpstr);
}