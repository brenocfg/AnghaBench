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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int DM ; 
 scalar_t__ ERROR ; 
 unsigned char IAC ; 
 unsigned char IP ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int /*<<< orphan*/  cin ; 
 int code ; 
 int /*<<< orphan*/ * cout ; 
 int empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lostpeer (int /*<<< orphan*/ ) ; 
 scalar_t__ ptabflg ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int send (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

void
abort_remote(FILE *din)
{
	unsigned char buf[BUFSIZ];
	int nfnd;

	if (cout == NULL) {
		warnx("Lost control connection for abort");
		if (ptabflg)
			code = -1;
		lostpeer(0);
		return;
	}
	/*
	 * send IAC in urgent mode instead of DM because 4.3BSD places oob mark
	 * after urgent byte rather than before as is protocol now
	 */
	buf[0] = IAC;
	buf[1] = IP;
	buf[2] = IAC;
	if (send(fileno(cout), buf, 3, MSG_OOB) != 3)
		warn("Can't send abort message");
	fprintf(cout, "%cABOR\r\n", DM);
	(void)fflush(cout);
	if ((nfnd = empty(cin, din, 10)) <= 0) {
		if (nfnd < 0)
			warn("Can't send abort message");
		if (ptabflg)
			code = -1;
		lostpeer(0);
	}
	if (din && (nfnd & 2)) {
		while (read(fileno(din), buf, BUFSIZ) > 0)
			continue;
	}
	if (getreply(0) == ERROR && code == 552) {
		/* 552 needed for nic style abort */
		(void)getreply(0);
	}
	(void)getreply(0);
}