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
struct message {int m_flag; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int MPRESERVE ; 
 int MTOUCH ; 
 int /*<<< orphan*/  alter (char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* mailname ; 
 struct message* message ; 
 size_t msgCount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ sendmessage (struct message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
writeback(FILE *res)
{
	struct message *mp;
	int p, c;
	FILE *obuf;

	p = 0;
	if ((obuf = Fopen(mailname, "r+")) == NULL) {
		warn("%s", mailname);
		return (-1);
	}
#ifndef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
			(void)putc(c, obuf);
#endif
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if ((mp->m_flag&MPRESERVE)||(mp->m_flag&MTOUCH)==0) {
			p++;
			if (sendmessage(mp, obuf, NULL, NULL) < 0) {
				warnx("%s", mailname);
				(void)Fclose(obuf);
				return (-1);
			}
		}
#ifdef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
			(void)putc(c, obuf);
#endif
	(void)fflush(obuf);
	trunc(obuf);
	if (ferror(obuf)) {
		warn("%s", mailname);
		(void)Fclose(obuf);
		return (-1);
	}
	if (res != NULL)
		(void)Fclose(res);
	(void)Fclose(obuf);
	alter(mailname);
	if (p == 1)
		printf("Held 1 message in %s\n", mailname);
	else
		printf("Held %d messages in %s\n", p, mailname);
	return (0);
}