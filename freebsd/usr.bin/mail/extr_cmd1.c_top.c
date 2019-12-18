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
struct message {int m_lines; } ;
typedef  int /*<<< orphan*/  linebuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINESIZE ; 
 int atoi (char*) ; 
 struct message* dot ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ readline (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * setinput (struct message*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 char* value (char*) ; 

int
top(void *v)
{
	int *msgvec = v;
	int *ip;
	struct message *mp;
	int c, topl, lines, lineb;
	char *valtop, linebuf[LINESIZE];
	FILE *ibuf;

	topl = 5;
	valtop = value("toplines");
	if (valtop != NULL) {
		topl = atoi(valtop);
		if (topl < 0 || topl > 10000)
			topl = 5;
	}
	lineb = 1;
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mp = &message[*ip - 1];
		touch(mp);
		dot = mp;
		if (value("quiet") == NULL)
			printf("Message %d:\n", *ip);
		ibuf = setinput(mp);
		c = mp->m_lines;
		if (!lineb)
			printf("\n");
		for (lines = 0; lines < c && lines <= topl; lines++) {
			if (readline(ibuf, linebuf, sizeof(linebuf)) < 0)
				break;
			puts(linebuf);
			lineb = strspn(linebuf, " \t") == strlen(linebuf);
		}
	}
	return (0);
}