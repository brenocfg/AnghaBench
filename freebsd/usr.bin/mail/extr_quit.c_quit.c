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
 int /*<<< orphan*/  LOCK_EX ; 
 int MBOX ; 
 int MDELETED ; 
 int MNEW ; 
 int MODIFY ; 
 int MPRESERVE ; 
 int MREAD ; 
 int MSAVED ; 
 int MSTATUS ; 
 int MTOUCH ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PATHSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* Tflag ; 
 int /*<<< orphan*/  alter (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  demail () ; 
 scalar_t__ edit ; 
 int /*<<< orphan*/  edstop () ; 
 char* expand (char*) ; 
 int /*<<< orphan*/  fchmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* hfield (char*,struct message*) ; 
 char* mailname ; 
 scalar_t__ mailsize ; 
 struct message* message ; 
 int mkstemp (char*) ; 
 size_t msgCount ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ readonly ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm (char*) ; 
 int /*<<< orphan*/  saveignore ; 
 scalar_t__ sendmessage (struct message*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* tmpdir ; 
 int /*<<< orphan*/  trunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * value (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 
 int /*<<< orphan*/  writeback (int /*<<< orphan*/ *) ; 

void
quit(void)
{
	int mcount, p, modify, autohold, anystat, holdbit, nohold;
	FILE *ibuf, *obuf, *fbuf, *rbuf, *readstat, *abuf;
	struct message *mp;
	int c, fd;
	struct stat minfo;
	char *mbox, tempname[PATHSIZE];

	/*
	 * If we are read only, we can't do anything,
	 * so just return quickly.
	 */
	if (readonly)
		return;
	/*
	 * If editing (not reading system mail box), then do the work
	 * in edstop()
	 */
	if (edit) {
		edstop();
		return;
	}

	/*
	 * See if there any messages to save in mbox.  If no, we
	 * can save copying mbox to /tmp and back.
	 *
	 * Check also to see if any files need to be preserved.
	 * Delete all untouched messages to keep them out of mbox.
	 * If all the messages are to be preserved, just exit with
	 * a message.
	 */

	fbuf = Fopen(mailname, "r");
	if (fbuf == NULL)
		goto newmail;
	(void)flock(fileno(fbuf), LOCK_EX);
	rbuf = NULL;
	if (fstat(fileno(fbuf), &minfo) >= 0 && minfo.st_size > mailsize) {
		printf("New mail has arrived.\n");
		(void)snprintf(tempname, sizeof(tempname),
		    "%s/mail.RqXXXXXXXXXX", tmpdir);
		if ((fd = mkstemp(tempname)) == -1 ||
		    (rbuf = Fdopen(fd, "w")) == NULL)
			goto newmail;
#ifdef APPEND
		(void)fseeko(fbuf, mailsize, SEEK_SET);
		while ((c = getc(fbuf)) != EOF)
			(void)putc(c, rbuf);
#else
		p = minfo.st_size - mailsize;
		while (p-- > 0) {
			c = getc(fbuf);
			if (c == EOF)
				goto newmail;
			(void)putc(c, rbuf);
		}
#endif
		(void)Fclose(rbuf);
		if ((rbuf = Fopen(tempname, "r")) == NULL)
			goto newmail;
		(void)rm(tempname);
	}

	/*
	 * Adjust the message flags in each message.
	 */

	anystat = 0;
	autohold = value("hold") != NULL;
	holdbit = autohold ? MPRESERVE : MBOX;
	nohold = MBOX|MSAVED|MDELETED|MPRESERVE;
	if (value("keepsave") != NULL)
		nohold &= ~MSAVED;
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & MSTATUS)
			anystat++;
		if ((mp->m_flag & MTOUCH) == 0)
			mp->m_flag |= MPRESERVE;
		if ((mp->m_flag & nohold) == 0)
			mp->m_flag |= holdbit;
	}
	modify = 0;
	if (Tflag != NULL) {
		if ((readstat = Fopen(Tflag, "w")) == NULL)
			Tflag = NULL;
	}
	for (c = 0, p = 0, mp = &message[0]; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MBOX)
			c++;
		if (mp->m_flag & MPRESERVE)
			p++;
		if (mp->m_flag & MODIFY)
			modify++;
		if (Tflag != NULL && (mp->m_flag & (MREAD|MDELETED)) != 0) {
			char *id;

			if ((id = hfield("article-id", mp)) != NULL)
				fprintf(readstat, "%s\n", id);
		}
	}
	if (Tflag != NULL)
		(void)Fclose(readstat);
	if (p == msgCount && !modify && !anystat) {
		printf("Held %d message%s in %s\n",
			p, p == 1 ? "" : "s", mailname);
		(void)Fclose(fbuf);
		return;
	}
	if (c == 0) {
		if (p != 0) {
			writeback(rbuf);
			(void)Fclose(fbuf);
			return;
		}
		goto cream;
	}

	/*
	 * Create another temporary file and copy user's mbox file
	 * darin.  If there is no mbox, copy nothing.
	 * If he has specified "append" don't copy his mailbox,
	 * just copy saveable entries at the end.
	 */

	mbox = expand("&");
	mcount = c;
	if (value("append") == NULL) {
		(void)snprintf(tempname, sizeof(tempname),
		    "%s/mail.RmXXXXXXXXXX", tmpdir);
		if ((fd = mkstemp(tempname)) == -1 ||
		    (obuf = Fdopen(fd, "w")) == NULL) {
			warn("%s", tempname);
			(void)Fclose(fbuf);
			return;
		}
		if ((ibuf = Fopen(tempname, "r")) == NULL) {
			warn("%s", tempname);
			(void)rm(tempname);
			(void)Fclose(obuf);
			(void)Fclose(fbuf);
			return;
		}
		(void)rm(tempname);
		if ((abuf = Fopen(mbox, "r")) != NULL) {
			while ((c = getc(abuf)) != EOF)
				(void)putc(c, obuf);
			(void)Fclose(abuf);
		}
		if (ferror(obuf)) {
			warnx("%s", tempname);
			(void)Fclose(ibuf);
			(void)Fclose(obuf);
			(void)Fclose(fbuf);
			return;
		}
		(void)Fclose(obuf);
		if ((fd = open(mbox, O_CREAT | O_TRUNC | O_WRONLY, 0600)) >= 0)
			(void)close(fd);
		if ((obuf = Fopen(mbox, "r+")) == NULL) {
			warn("%s", mbox);
			(void)Fclose(ibuf);
			(void)Fclose(fbuf);
			return;
		}
	}
	if (value("append") != NULL) {
		if ((obuf = Fopen(mbox, "a")) == NULL) {
			warn("%s", mbox);
			(void)Fclose(fbuf);
			return;
		}
		(void)fchmod(fileno(obuf), 0600);
	}
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if (mp->m_flag & MBOX)
			if (sendmessage(mp, obuf, saveignore, NULL) < 0) {
				warnx("%s", mbox);
				(void)Fclose(ibuf);
				(void)Fclose(obuf);
				(void)Fclose(fbuf);
				return;
			}

	/*
	 * Copy the user's old mbox contents back
	 * to the end of the stuff we just saved.
	 * If we are appending, this is unnecessary.
	 */

	if (value("append") == NULL) {
		rewind(ibuf);
		c = getc(ibuf);
		while (c != EOF) {
			(void)putc(c, obuf);
			if (ferror(obuf))
				break;
			c = getc(ibuf);
		}
		(void)Fclose(ibuf);
	}
	(void)fflush(obuf);
	trunc(obuf);
	if (ferror(obuf)) {
		warn("%s", mbox);
		(void)Fclose(obuf);
		(void)Fclose(fbuf);
		return;
	}
	(void)Fclose(obuf);
	if (mcount == 1)
		printf("Saved 1 message in mbox\n");
	else
		printf("Saved %d messages in mbox\n", mcount);

	/*
	 * Now we are ready to copy back preserved files to
	 * the system mailbox, if any were requested.
	 */

	if (p != 0) {
		writeback(rbuf);
		(void)Fclose(fbuf);
		return;
	}

	/*
	 * Finally, remove his /var/mail file.
	 * If new mail has arrived, copy it back.
	 */

cream:
	if (rbuf != NULL) {
		abuf = Fopen(mailname, "r+");
		if (abuf == NULL)
			goto newmail;
		while ((c = getc(rbuf)) != EOF)
			(void)putc(c, abuf);
		(void)Fclose(rbuf);
		trunc(abuf);
		(void)Fclose(abuf);
		alter(mailname);
		(void)Fclose(fbuf);
		return;
	}
	demail();
	(void)Fclose(fbuf);
	return;

newmail:
	printf("Thou hast new mail.\n");
	if (fbuf != NULL)
		(void)Fclose(fbuf);
}