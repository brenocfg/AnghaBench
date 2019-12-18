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
typedef  int /*<<< orphan*/  tempname ;
struct stat {scalar_t__ st_size; } ;
struct message {int m_flag; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fdopen (int,char*) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int MDELETED ; 
 int MNEW ; 
 int MODIFY ; 
 int MREAD ; 
 int MSTATUS ; 
 int PATHSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* Tflag ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* hfield (char*,struct message*) ; 
 int /*<<< orphan*/  holdsigs () ; 
 char* mailname ; 
 scalar_t__ mailsize ; 
 struct message* message ; 
 int mkstemp (char*) ; 
 size_t msgCount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ readonly ; 
 int /*<<< orphan*/  relsesigs () ; 
 int /*<<< orphan*/  reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm (char*) ; 
 scalar_t__ sendmessage (struct message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/ * stdout ; 
 char* tmpdir ; 
 int /*<<< orphan*/  trunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

void
edstop(void)
{
	int gotcha, c;
	struct message *mp;
	FILE *obuf, *ibuf, *readstat;
	struct stat statb;
	char tempname[PATHSIZE];

	if (readonly)
		return;
	holdsigs();
	if (Tflag != NULL) {
		if ((readstat = Fopen(Tflag, "w")) == NULL)
			Tflag = NULL;
	}
	for (mp = &message[0], gotcha = 0; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & (MODIFY|MDELETED|MSTATUS))
			gotcha++;
		if (Tflag != NULL && (mp->m_flag & (MREAD|MDELETED)) != 0) {
			char *id;

			if ((id = hfield("article-id", mp)) != NULL)
				fprintf(readstat, "%s\n", id);
		}
	}
	if (Tflag != NULL)
		(void)Fclose(readstat);
	if (!gotcha || Tflag != NULL)
		goto done;
	ibuf = NULL;
	if (stat(mailname, &statb) >= 0 && statb.st_size > mailsize) {
		int fd;

		(void)snprintf(tempname, sizeof(tempname),
		    "%s/mbox.XXXXXXXXXX", tmpdir);
		if ((fd = mkstemp(tempname)) == -1 ||
		    (obuf = Fdopen(fd, "w")) == NULL) {
			warn("%s", tempname);
			relsesigs();
			reset(0);
		}
		if ((ibuf = Fopen(mailname, "r")) == NULL) {
			warn("%s", mailname);
			(void)Fclose(obuf);
			(void)rm(tempname);
			relsesigs();
			reset(0);
		}
		(void)fseeko(ibuf, mailsize, SEEK_SET);
		while ((c = getc(ibuf)) != EOF)
			(void)putc(c, obuf);
		(void)Fclose(ibuf);
		(void)Fclose(obuf);
		if ((ibuf = Fopen(tempname, "r")) == NULL) {
			warn("%s", tempname);
			(void)rm(tempname);
			relsesigs();
			reset(0);
		}
		(void)rm(tempname);
	}
	printf("\"%s\" ", mailname);
	(void)fflush(stdout);
	if ((obuf = Fopen(mailname, "r+")) == NULL) {
		warn("%s", mailname);
		relsesigs();
		reset(0);
	}
	trunc(obuf);
	c = 0;
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
		if ((mp->m_flag & MDELETED) != 0)
			continue;
		c++;
		if (sendmessage(mp, obuf, NULL, NULL) < 0) {
			warnx("%s", mailname);
			relsesigs();
			reset(0);
		}
	}
	gotcha = (c == 0 && ibuf == NULL);
	if (ibuf != NULL) {
		while ((c = getc(ibuf)) != EOF)
			(void)putc(c, obuf);
		(void)Fclose(ibuf);
	}
	(void)fflush(obuf);
	if (ferror(obuf)) {
		warn("%s", mailname);
		relsesigs();
		reset(0);
	}
	(void)Fclose(obuf);
	if (gotcha) {
		(void)rm(mailname);
		printf("removed\n");
	} else
		printf("complete\n");
	(void)fflush(stdout);

done:
	relsesigs();
}