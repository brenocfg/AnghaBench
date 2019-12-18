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
struct message {int /*<<< orphan*/  m_flag; } ;
struct ignoretab {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int /*<<< orphan*/  MMNORM ; 
 int /*<<< orphan*/  MSAVED ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* expand (char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getmsglist (char*,int*,int /*<<< orphan*/ ) ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ salloc (int) ; 
 scalar_t__ sendmessage (struct message*,int /*<<< orphan*/ *,struct ignoretab*,int /*<<< orphan*/ *) ; 
 char* snarf (char*,int*) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
save1(char str[], int mark, const char *cmd, struct ignoretab *ignore)
{
	struct message *mp;
	char *file;
	const char *disp;
	int f, *msgvec, *ip;
	FILE *obuf;

	msgvec = (int *)salloc((msgCount + 2) * sizeof(*msgvec));
	if ((file = snarf(str, &f)) == NULL)
		return (1);
	if (!f) {
		*msgvec = first(0, MMNORM);
		if (*msgvec == 0) {
			printf("No messages to %s.\n", cmd);
			return (1);
		}
		msgvec[1] = 0;
	}
	if (f && getmsglist(str, msgvec, 0) < 0)
		return (1);
	if ((file = expand(file)) == NULL)
		return (1);
	printf("\"%s\" ", file);
	(void)fflush(stdout);
	if (access(file, 0) >= 0)
		disp = "[Appended]";
	else
		disp = "[New file]";
	if ((obuf = Fopen(file, "a")) == NULL) {
		warn((char *)NULL);
		return (1);
	}
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mp = &message[*ip - 1];
		touch(mp);
		if (sendmessage(mp, obuf, ignore, NULL) < 0) {
			warnx("%s", file);
			(void)Fclose(obuf);
			return (1);
		}
		if (mark)
			mp->m_flag |= MSAVED;
	}
	(void)fflush(obuf);
	if (ferror(obuf))
		warn("%s", file);
	(void)Fclose(obuf);
	printf("%s\n", disp);
	return (0);
}