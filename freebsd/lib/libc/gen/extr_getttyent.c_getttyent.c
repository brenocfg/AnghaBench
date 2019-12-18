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
struct ttyent {char* ty_name; char* ty_getty; char* ty_type; char* ty_comment; void* ty_group; int /*<<< orphan*/ * ty_window; int /*<<< orphan*/  ty_status; } ;

/* Variables and functions */
 scalar_t__ MALLOCCHUNK ; 
 int /*<<< orphan*/  TTY_DIALUP ; 
 int /*<<< orphan*/  TTY_NETWORK ; 
 int /*<<< orphan*/  TTY_ON ; 
 int /*<<< orphan*/  TTY_SECURE ; 
 int /*<<< orphan*/  _TTYS_DIALUP ; 
 int /*<<< orphan*/  _TTYS_GROUP ; 
 int /*<<< orphan*/  _TTYS_INSECURE ; 
 int /*<<< orphan*/  _TTYS_NETWORK ; 
 void* _TTYS_NOGROUP ; 
 int /*<<< orphan*/  _TTYS_OFF ; 
 int /*<<< orphan*/  _TTYS_ON ; 
 int /*<<< orphan*/  _TTYS_ONIFCONSOLE ; 
 int /*<<< orphan*/  _TTYS_ONIFEXISTS ; 
 int /*<<< orphan*/  _TTYS_SECURE ; 
 int /*<<< orphan*/  _TTYS_WINDOW ; 
 int /*<<< orphan*/  auto_exists_status (char*) ; 
 int /*<<< orphan*/  auto_tty_status (char*) ; 
 int /*<<< orphan*/  endttyent () ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ lbsize ; 
 char* line ; 
 char* realloc (char*,scalar_t__) ; 
 scalar_t__ scmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setttyent () ; 
 char* skip (char*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  tf ; 
 void* value (char*) ; 
 scalar_t__ vcmp (int /*<<< orphan*/ ) ; 
 char zapchar ; 

struct ttyent *
getttyent(void)
{
	static struct ttyent tty;
	char *p;
	int c;
	size_t i;

	if (!tf && !setttyent())
		return (NULL);
	for (;;) {
		if (!fgets(p = line, lbsize, tf))
			return (NULL);
		/* extend buffer if line was too big, and retry */
		while (!strchr(p, '\n') && !feof(tf)) {
			i = strlen(p);
			lbsize += MALLOCCHUNK;
			if ((p = realloc(line, lbsize)) == NULL) {
				(void)endttyent();
				return (NULL);
			}
			line = p;
			if (!fgets(&line[i], lbsize - i, tf))
				return (NULL);
		}
		while (isspace((unsigned char)*p))
			++p;
		if (*p && *p != '#')
			break;
	}

#define scmp(e) !strncmp(p, e, sizeof(e) - 1) && isspace((unsigned char)p[sizeof(e) - 1])
#define	vcmp(e)	!strncmp(p, e, sizeof(e) - 1) && p[sizeof(e) - 1] == '='

	zapchar = 0;
	tty.ty_name = p;
	tty.ty_status = 0;
	tty.ty_window = NULL;
	tty.ty_group  = _TTYS_NOGROUP;

	p = skip(p);
	if (!*(tty.ty_getty = p))
		tty.ty_getty = tty.ty_type = NULL;
	else {
		p = skip(p);
		if (!*(tty.ty_type = p))
			tty.ty_type = NULL;
		else {
			/* compatibility kludge: handle network/dialup specially */
			if (scmp(_TTYS_DIALUP))
				tty.ty_status |= TTY_DIALUP;
			else if (scmp(_TTYS_NETWORK))
				tty.ty_status |= TTY_NETWORK;
			p = skip(p);
		}
	}

	for (; *p; p = skip(p)) {
		if (scmp(_TTYS_OFF))
			tty.ty_status &= ~TTY_ON;
		else if (scmp(_TTYS_ON))
			tty.ty_status |= TTY_ON;
		else if (scmp(_TTYS_ONIFCONSOLE))
			tty.ty_status |= auto_tty_status(tty.ty_name);
		else if (scmp(_TTYS_ONIFEXISTS))
			tty.ty_status |= auto_exists_status(tty.ty_name);
		else if (scmp(_TTYS_SECURE))
			tty.ty_status |= TTY_SECURE;
		else if (scmp(_TTYS_INSECURE))
			tty.ty_status &= ~TTY_SECURE;
		else if (scmp(_TTYS_DIALUP))
			tty.ty_status |= TTY_DIALUP;
		else if (scmp(_TTYS_NETWORK))
			tty.ty_status |= TTY_NETWORK;
		else if (vcmp(_TTYS_WINDOW))
			tty.ty_window = value(p);
		else if (vcmp(_TTYS_GROUP))
			tty.ty_group = value(p);
		else
			break;
	}

	if (zapchar == '#' || *p == '#')
		while ((c = *++p) == ' ' || c == '\t')
			;
	tty.ty_comment = p;
	if (*p == 0)
		tty.ty_comment = 0;
	if ((p = strchr(p, '\n')))
		*p = '\0';
	return (&tty);
}