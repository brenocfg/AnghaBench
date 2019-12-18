#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {char* oname; TYPE_1__* focus; } ;
struct TYPE_9__ {int /*<<< orphan*/ * gp; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  GS ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_2__* CLP (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_RENAME ; 
 int /*<<< orphan*/  CL_RENAME_OK ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GO_TERM ; 
 int /*<<< orphan*/  OG_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_setname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 char* strndup (char*,int) ; 
 char* strrchr (char*,char) ; 

int
cl_rename(SCR *sp, char *name, int on)
{
	GS *gp;
	CL_PRIVATE *clp;
	FILE *pfp;
	char buf[256], *s, *e;
	char * wid;
	char cmd[64];

	gp = sp->gp;
	clp = CLP(sp);

	/*
	 * XXX
	 * We can only rename windows for xterm.
	 */
	if (on) {
		clp->focus = sp;
		if (!F_ISSET(clp, CL_RENAME_OK) ||
		    strncmp(OG_STR(gp, GO_TERM), "xterm", 5))
			return (0);

		if (clp->oname == NULL && (wid = getenv("WINDOWID"))) {
			snprintf(cmd, sizeof(cmd), "xprop -id %s WM_NAME", wid);
			if ((pfp = popen(cmd, "r")) == NULL)
				goto rename;
			if (fgets(buf, sizeof(buf), pfp) == NULL) {
				pclose(pfp);
				goto rename;
			}
			pclose(pfp);
			if ((s = strchr(buf, '"')) != NULL &&
			    (e = strrchr(buf, '"')) != NULL)
				clp->oname = strndup(s + 1, e - s - 1);
		}

rename:		cl_setname(gp, name);

		F_SET(clp, CL_RENAME);
	} else
		if (F_ISSET(clp, CL_RENAME)) {
			cl_setname(gp, clp->oname);

			F_CLR(clp, CL_RENAME);
		}
	return (0);
}