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
struct message {long m_size; scalar_t__ m_lines; int /*<<< orphan*/  m_flag; int /*<<< orphan*/  m_offset; int /*<<< orphan*/  m_block; } ;
typedef  int /*<<< orphan*/  sig_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MODIFY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  blockof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boffsetof (int /*<<< orphan*/ ) ; 
 struct message* dot ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftello (int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  otf ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int putc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readonly ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * run_editor (int /*<<< orphan*/ ,long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setinput (struct message*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
edit1(int *msgvec, int type)
{
	int c, i;
	FILE *fp;
	struct message *mp;
	off_t size;

	/*
	 * Deal with each message to be edited . . .
	 */
	for (i = 0; i < msgCount && msgvec[i]; i++) {
		sig_t sigint;

		if (i > 0) {
			char buf[100];
			char *p;

			printf("Edit message %d [ynq]? ", msgvec[i]);
			if (fgets(buf, sizeof(buf), stdin) == NULL)
				break;
			for (p = buf; *p == ' ' || *p == '\t'; p++)
				;
			if (*p == 'q')
				break;
			if (*p == 'n')
				continue;
		}
		dot = mp = &message[msgvec[i] - 1];
		touch(mp);
		sigint = signal(SIGINT, SIG_IGN);
		fp = run_editor(setinput(mp), mp->m_size, type, readonly);
		if (fp != NULL) {
			(void)fseeko(otf, (off_t)0, SEEK_END);
			size = ftello(otf);
			mp->m_block = blockof(size);
			mp->m_offset = boffsetof(size);
			mp->m_size = (long)fsize(fp);
			mp->m_lines = 0;
			mp->m_flag |= MODIFY;
			rewind(fp);
			while ((c = getc(fp)) != EOF) {
				if (c == '\n')
					mp->m_lines++;
				if (putc(c, otf) == EOF)
					break;
			}
			if (ferror(otf))
				warnx("/tmp");
			(void)Fclose(fp);
		}
		(void)signal(SIGINT, sigint);
	}
	return (0);
}