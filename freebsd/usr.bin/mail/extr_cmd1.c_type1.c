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
struct message {scalar_t__ m_lines; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Popen (char*,char*) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 char* _PATH_LESS ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  brokpipe ; 
 struct message* dot ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ignore ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  pipestop ; 
 int realscreenheight ; 
 int /*<<< orphan*/  sendmessage (struct message*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 char* value (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
type1(int *msgvec, int doign, int page)
{
	int nlines, *ip;
	struct message *mp;
	char *cp;
	FILE *obuf;

	obuf = stdout;
	if (setjmp(pipestop))
		goto close_pipe;
	if (value("interactive") != NULL &&
	    (page || (cp = value("crt")) != NULL)) {
		nlines = 0;
		if (!page) {
			for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++)
				nlines += message[*ip - 1].m_lines;
		}
		if (page || nlines > (*cp ? atoi(cp) : realscreenheight)) {
			cp = value("PAGER");
			if (cp == NULL || *cp == '\0')
				cp = _PATH_LESS;
			obuf = Popen(cp, "w");
			if (obuf == NULL) {
				warnx("%s", cp);
				obuf = stdout;
			} else
				(void)signal(SIGPIPE, brokpipe);
		}
	}

	/*
	 * Send messages to the output.
	 *
	 */
	for (ip = msgvec; *ip && ip - msgvec < msgCount; ip++) {
		mp = &message[*ip - 1];
		touch(mp);
		dot = mp;
		if (value("quiet") == NULL)
			fprintf(obuf, "Message %d:\n", *ip);
		(void)sendmessage(mp, obuf, doign ? ignore : 0, NULL);
	}

close_pipe:
	if (obuf != stdout) {
		/*
		 * Ignore SIGPIPE so it can't cause a duplicate close.
		 */
		(void)signal(SIGPIPE, SIG_IGN);
		(void)Pclose(obuf);
		(void)signal(SIGPIPE, SIG_DFL);
	}
	return (0);
}