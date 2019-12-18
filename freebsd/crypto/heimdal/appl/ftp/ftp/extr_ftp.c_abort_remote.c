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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int DM ; 
 scalar_t__ ERROR ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int IAC ; 
 int IP ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int /*<<< orphan*/ * cin ; 
 int code ; 
 int /*<<< orphan*/ * cout ; 
 int empty (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lostpeer (int /*<<< orphan*/ ) ; 
 scalar_t__ ptabflg ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sec_fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_fprintf (int /*<<< orphan*/ *,char*) ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

void
abort_remote (FILE * din)
{
    char buf[BUFSIZ];
    int nfnd;
    fd_set mask;

    /*
     * send IAC in urgent mode instead of DM because 4.3BSD places oob mark
     * after urgent byte rather than before as is protocol now
     */
    snprintf (buf, sizeof (buf), "%c%c%c", IAC, IP, IAC);
    if (send (fileno (cout), buf, 3, MSG_OOB) != 3)
	warn ("abort");
    fprintf (cout, "%c", DM);
    sec_fprintf(cout, "ABOR");
    sec_fflush (cout);
    fprintf (cout, "\r\n");
    fflush(cout);
    FD_ZERO (&mask);
    if (fileno (cin) >= FD_SETSIZE)
	errx (1, "fd too large");
    FD_SET (fileno (cin), &mask);
    if (din) {
	if (fileno (din) >= FD_SETSIZE)
	    errx (1, "fd too large");
	FD_SET (fileno (din), &mask);
    }
    if ((nfnd = empty (&mask, 10)) <= 0) {
	if (nfnd < 0) {
	    warn ("abort");
	}
	if (ptabflg)
	    code = -1;
	lostpeer (0);
    }
    if (din && FD_ISSET (fileno (din), &mask)) {
	while (read (fileno (din), buf, BUFSIZ) > 0)
	     /* LOOP */ ;
    }
    if (getreply (0) == ERROR && code == 552) {
	/* 552 needed for nic style abort */
	getreply (0);
    }
    getreply (0);
}