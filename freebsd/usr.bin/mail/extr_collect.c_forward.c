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
struct message {int dummy; } ;
struct ignoretab {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MMNORM ; 
 int first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getmsglist (char*,int*,int /*<<< orphan*/ ) ; 
 struct ignoretab* ignore ; 
 scalar_t__ isupper (unsigned char) ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ salloc (int) ; 
 scalar_t__ sendmessage (struct message*,int /*<<< orphan*/ *,struct ignoretab*,char*) ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 char* value (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
forward(char ms[], FILE *fp, char *fn, int f)
{
	int *msgvec;
	struct ignoretab *ig;
	char *tabst;

	msgvec = (int *)salloc((msgCount+1) * sizeof(*msgvec));
	if (msgvec == NULL)
		return (0);
	if (getmsglist(ms, msgvec, 0) < 0)
		return (0);
	if (*msgvec == 0) {
		*msgvec = first(0, MMNORM);
		if (*msgvec == 0) {
			printf("No appropriate messages\n");
			return (0);
		}
		msgvec[1] = 0;
	}
	if (f == 'f' || f == 'F')
		tabst = NULL;
	else if ((tabst = value("indentprefix")) == NULL)
		tabst = "\t";
	ig = isupper((unsigned char)f) ? NULL : ignore;
	printf("Interpolating:");
	for (; *msgvec != 0; msgvec++) {
		struct message *mp = message + *msgvec - 1;

		touch(mp);
		printf(" %d", *msgvec);
		if (sendmessage(mp, fp, ig, tabst) < 0) {
			warnx("%s", fn);
			return (-1);
		}
	}
	printf("\n");
	return (0);
}