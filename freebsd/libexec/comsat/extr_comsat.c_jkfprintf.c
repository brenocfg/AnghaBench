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
struct passwd {int /*<<< orphan*/  pw_uid; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 char* cr ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ iscntrl (unsigned char) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 

__attribute__((used)) static void
jkfprintf(FILE *tp, char user[], char file[], off_t offset)
{
	unsigned char *cp, ch;
	FILE *fi;
	int linecnt, charcnt, inheader;
	struct passwd *p;
	unsigned char line[BUFSIZ];

	/* Set effective uid to user in case mail drop is on nfs */
	if ((p = getpwnam(user)) != NULL)
		(void) setuid(p->pw_uid);

	if ((fi = fopen(file, "r")) == NULL)
		return;

	(void)fseeko(fi, offset, SEEK_CUR);
	/*
	 * Print the first 7 lines or 560 characters of the new mail
	 * (whichever comes first).  Skip header crap other than
	 * From, Subject, To, and Date.
	 */
	linecnt = 7;
	charcnt = 560;
	inheader = 1;
	while (fgets(line, sizeof(line), fi) != NULL) {
		if (inheader) {
			if (line[0] == '\n') {
				inheader = 0;
				continue;
			}
			if (line[0] == ' ' || line[0] == '\t' ||
			    (strncmp(line, "From:", 5) &&
			    strncmp(line, "Subject:", 8)))
				continue;
		}
		if (linecnt <= 0 || charcnt <= 0) {
			(void)fprintf(tp, "...more...%s", cr);
			(void)fclose(fi);
			return;
		}
		/* strip weird stuff so can't trojan horse stupid terminals */
		for (cp = line; (ch = *cp) && ch != '\n'; ++cp, --charcnt) {
			/* disable upper controls and enable all other
			   8bit codes due to lack of locale knowledge
			 */
			if (((ch & 0x80) && ch < 0xA0) ||
			    (!(ch & 0x80) && !isprint(ch) &&
			     !isspace(ch) && ch != '\a' && ch != '\b')
			   ) {
				if (ch & 0x80) {
					ch &= ~0x80;
					(void)fputs("M-", tp);
				}
				if (iscntrl(ch)) {
					ch ^= 0x40;
					(void)fputc('^', tp);
				}
			}
			(void)fputc(ch, tp);
		}
		(void)fputs(cr, tp);
		--linecnt;
	}
	(void)fprintf(tp, "----%s\n", cr);
	(void)fclose(fi);
}