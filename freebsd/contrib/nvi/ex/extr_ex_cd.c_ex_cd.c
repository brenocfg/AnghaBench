#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct passwd {char* pw_dir; } ;
struct TYPE_14__ {char* bp; int len; } ;
struct TYPE_13__ {int argc; TYPE_4__** argv; int /*<<< orphan*/  iflags; } ;
struct TYPE_12__ {TYPE_1__* frp; int /*<<< orphan*/  ep; } ;
struct TYPE_11__ {char* name; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXCMD ;
typedef  TYPE_4__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_MODIFIED ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_2__*,char*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_CDPATH ; 
 char* O_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 char* join (char*,char*) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgq_str (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 

int
ex_cd(SCR *sp, EXCMD *cmdp)
{
	struct passwd *pw;
	ARGS *ap;
	int savech;
	char *dir, *p, *t;
	char *buf;
	size_t dlen;

	/*
	 * !!!
	 * Historic practice is that the cd isn't attempted if the file has
	 * been modified, unless its name begins with a leading '/' or the
	 * force flag is set.
	 */
	if (F_ISSET(sp->ep, F_MODIFIED) &&
	    !FL_ISSET(cmdp->iflags, E_C_FORCE) && sp->frp->name[0] != '/') {
		msgq(sp, M_ERR,
    "120|File modified since last complete write; write or use ! to override");
		return (1);
	}

	switch (cmdp->argc) {
	case 0:
		/* If no argument, change to the user's home directory. */
		if ((dir = getenv("HOME")) == NULL) {
			if ((pw = getpwuid(getuid())) == NULL ||
			    pw->pw_dir == NULL || pw->pw_dir[0] == '\0') {
				msgq(sp, M_ERR,
			   "121|Unable to find home directory location");
				return (1);
			}
			dir = pw->pw_dir;
		}
		break;
	case 1:
		INT2CHAR(sp, cmdp->argv[0]->bp, cmdp->argv[0]->len + 1, 
			 dir, dlen);
		break;
	default:
		abort();
	}

	/*
	 * Try the current directory first.  If this succeeds, don't display
	 * a message, vi didn't historically, and it should be obvious to the
	 * user where they are.
	 */
	if (!chdir(dir))
		return (0);

	/*
	 * If moving to the user's home directory, or, the path begins with
	 * "/", "./" or "../", it's the only place we try.
	 */
	if (cmdp->argc == 0 ||
	    (ap = cmdp->argv[0])->bp[0] == '/' ||
	    (ap->len == 1 && ap->bp[0] == '.') ||
	    (ap->len >= 2 && ap->bp[0] == '.' && ap->bp[1] == '.' &&
	    (ap->bp[2] == '/' || ap->bp[2] == '\0')))
		goto err;

	/* Try the O_CDPATH option values. */
	for (p = t = O_STR(sp, O_CDPATH);; ++p)
		if (*p == '\0' || *p == ':') {
			/*
			 * Ignore the empty strings and ".", since we've already
			 * tried the current directory.
			 */
			if (t < p && (p - t != 1 || *t != '.')) {
				savech = *p;
				*p = '\0';
				if ((buf = join(t, dir)) == NULL) {
					msgq(sp, M_SYSERR, NULL);
					return (1);
				}
				*p = savech;
				if (!chdir(buf)) {
					free(buf);
					if ((buf = getcwd(NULL, 0)) != NULL) {
		msgq_str(sp, M_INFO, buf, "122|New current directory: %s");
						free(buf);
					}
					return (0);
				}
				free(buf);
			}
			t = p + 1;
			if (*p == '\0')
				break;
		}

err:	msgq_str(sp, M_SYSERR, dir, "%s");
	return (1);
}