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
typedef  int /*<<< orphan*/  zname ;
struct message {int m_flag; } ;
typedef  int /*<<< orphan*/  fname ;

/* Variables and functions */
 int MDELETED ; 
 int MNEW ; 
 int MREAD ; 
 int MSAVED ; 
 int /*<<< orphan*/  PATHSIZE ; 
 scalar_t__ getfold (char*,int) ; 
 char* mailname ; 
 struct message* message ; 
 size_t msgCount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ readonly ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
newfileinfo(int omsgCount)
{
	struct message *mp;
	int u, n, mdot, d, s;
	char fname[PATHSIZE+1], zname[PATHSIZE+1], *ename;

	for (mp = &message[omsgCount]; mp < &message[msgCount]; mp++)
		if (mp->m_flag & MNEW)
			break;
	if (mp >= &message[msgCount])
		for (mp = &message[omsgCount]; mp < &message[msgCount]; mp++)
			if ((mp->m_flag & MREAD) == 0)
				break;
	if (mp < &message[msgCount])
		mdot = mp - &message[0] + 1;
	else
		mdot = omsgCount + 1;
	s = d = 0;
	for (mp = &message[0], n = 0, u = 0; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW)
			n++;
		if ((mp->m_flag & MREAD) == 0)
			u++;
		if (mp->m_flag & MDELETED)
			d++;
		if (mp->m_flag & MSAVED)
			s++;
	}
	ename = mailname;
	if (getfold(fname, sizeof(fname) - 1) >= 0) {
		strcat(fname, "/");
		if (strncmp(fname, mailname, strlen(fname)) == 0) {
			(void)snprintf(zname, sizeof(zname), "+%s",
			    mailname + strlen(fname));
			ename = zname;
		}
	}
	printf("\"%s\": ", ename);
	if (msgCount == 1)
		printf("1 message");
	else
		printf("%d messages", msgCount);
	if (n > 0)
		printf(" %d new", n);
	if (u-n > 0)
		printf(" %d unread", u);
	if (d > 0)
		printf(" %d deleted", d);
	if (s > 0)
		printf(" %d saved", s);
	if (readonly)
		printf(" [Read only]");
	printf("\n");
	return (mdot);
}