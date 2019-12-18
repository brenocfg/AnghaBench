#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nl_catd ;
struct TYPE_7__ {int /*<<< orphan*/  catd; } ;
struct TYPE_6__ {TYPE_5__* gp; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 scalar_t__ EFTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  NL_CAT_LOCALE ; 
 int /*<<< orphan*/  catopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join (char*,char*) ; 
 int /*<<< orphan*/  msg_close (TYPE_5__*) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq_str (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* setlocale (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strrchr (char*,char) ; 

int
msg_open(
	SCR *sp,
	char *file)
{
	/*
	 * !!!
	 * Assume that the first file opened is the system default, and that
	 * all subsequent ones user defined.  Only display error messages
	 * if we can't open the user defined ones -- it's useful to know if
	 * the system one wasn't there, but if nvi is being shipped with an
	 * installed system, the file will be there, if it's not, then the
	 * message will be repeated every time nvi is started up.
	 */
	static int first = 1;
	nl_catd catd;
	char *p;
	int rval = 0;

	if ((p = strrchr(file, '/')) != NULL && p[1] == '\0') {
		/* Confirms to XPG4. */
		if ((p = join(file, setlocale(LC_MESSAGES, NULL))) == NULL) {
			msgq(sp, M_SYSERR, NULL);
			return (1);
		}
	} else {
		/* Make sure it's recognized as a path by catopen(3). */
		if ((p = join(".", file)) == NULL) {
			msgq(sp, M_SYSERR, NULL);
			return (1);
		}
	}
	errno = 0;
	if ((catd = catopen(p, NL_CAT_LOCALE)) == (nl_catd)-1) {
		if (first) {
			first = 0;
			rval = 1;
			goto ret;
		}

		/*
		 * POSIX.1-2008 gives no instruction on how to report a
		 * corrupt catalog file.  Errno == 0 is not rare; add
		 * EFTYPE, which is seen on FreeBSD, for a good measure.
		 */
		if (errno == 0 || errno == EFTYPE)
			msgq_str(sp, M_ERR, p,
			    "030|The file %s is not a message catalog");
		else
			msgq_str(sp, M_SYSERR, p, "%s");
		rval = 1;
		goto ret;
	}
	first = 0;

	msg_close(sp->gp);
	sp->gp->catd = catd;
ret:	free(p);
	return (rval);
}