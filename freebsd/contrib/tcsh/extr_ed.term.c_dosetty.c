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
struct tcshmodes {int m_type; int m_value; int /*<<< orphan*/  m_name; } ;
struct command {int dummy; } ;
struct TYPE_2__ {int t_setmask; int t_clrmask; int /*<<< orphan*/  t_name; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int ED_IO ; 
 int ERR_NAME ; 
 int ERR_SYSTEM ; 
 int EX_IO ; 
 int QU_IO ; 
 int TermH ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int didsetty ; 
 struct tcshmodes* modelist ; 
 int /*<<< orphan*/  setname (char*) ; 
 char* short2str (char*) ; 
 int /*<<< orphan*/  stderror (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 char* strsave (char*) ; 
 TYPE_1__** ttylist ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xprintf (char*,...) ; 
 int /*<<< orphan*/  xputchar (char) ; 

void
dosetty(Char **v, struct command *t)
{
    const struct tcshmodes *m;
    char x, *d, *cmdname;
    int aflag = 0;
    Char *s;
    int z = EX_IO;

    USE(t);
    cmdname = strsave(short2str(*v++));
    cleanup_push(cmdname, xfree);
    setname(cmdname);

    while (v && *v && v[0][0] == '-' && v[0][2] == '\0') 
	switch (v[0][1]) {
	case 'a':
	    aflag++;
	    v++;
	    break;
	case 'd':
	    v++;
	    z = ED_IO;
	    break;
	case 'x':
	    v++;
	    z = EX_IO;
	    break;
	case 'q':
	    v++;
	    z = QU_IO;
	    break;
	default:
	    stderror(ERR_NAME | ERR_SYSTEM, short2str(v[0]),
		     CGETS(8, 1, "Unknown switch"));
	    break;
	}

    didsetty = 1;
    if (!v || !*v) {
	int i = -1;
	int len = 0, st = 0, cu;
	for (m = modelist; m->m_name; m++) {
	    if (m->m_type != i) {
		xprintf("%s%s", i != -1 ? "\n" : "",
			ttylist[z][m->m_type].t_name);
		i = m->m_type;
		st = len = strlen(ttylist[z][m->m_type].t_name);
	    }
	    assert(i != -1);

	    x = (ttylist[z][i].t_setmask & m->m_value) ? '+' : '\0';
	    x = (ttylist[z][i].t_clrmask & m->m_value) ? '-' : x;

	    if (x != '\0' || aflag) {
		cu = strlen(m->m_name) + (x != '\0') + 1;
		if (len + cu >= TermH) {
		    xprintf("\n%*s", st, "");
		    len = st + cu;
		}
		else 
		    len += cu;
		if (x != '\0')
		    xprintf("%c%s ", x, m->m_name);
		else
		    xprintf("%s ", m->m_name);
	    }
	}
	xputchar('\n');
	cleanup_until(cmdname);
	return;
    }
    while (v && (s = *v++)) {
	switch (*s) {
	case '+':
	case '-':
	    x = *s++;
	    break;
	default:
	    x = '\0';
	    break;
	}
	d = short2str(s);
	for (m = modelist; m->m_name; m++)
	    if (strcmp(m->m_name, d) == 0)
		break;
	if (!m->m_name) 
	    stderror(ERR_NAME | ERR_SYSTEM, d, CGETS(8, 2, "Invalid argument"));

	switch (x) {
	case '+':
	    ttylist[z][m->m_type].t_setmask |= m->m_value;
	    ttylist[z][m->m_type].t_clrmask &= ~m->m_value;
	    break;
	case '-':
	    ttylist[z][m->m_type].t_setmask &= ~m->m_value;
	    ttylist[z][m->m_type].t_clrmask |= m->m_value;
	    break;
	default:
	    ttylist[z][m->m_type].t_setmask &= ~m->m_value;
	    ttylist[z][m->m_type].t_clrmask &= ~m->m_value;
	    break;
	}
    }
    cleanup_until(cmdname);
}