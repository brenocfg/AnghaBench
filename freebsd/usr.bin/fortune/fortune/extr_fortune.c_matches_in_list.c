#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int str_flags; char str_delim; } ;
struct TYPE_5__ {char* name; TYPE_4__ tbl; int /*<<< orphan*/  inf; int /*<<< orphan*/  path; struct TYPE_5__* child; struct TYPE_5__* next; } ;
typedef  TYPE_1__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  Fort_len ; 
 char* Fortbuf ; 
 void* Found_one ; 
 scalar_t__ REG_NOMATCH ; 
 int /*<<< orphan*/  Re_pat ; 
 int STR_COMMENTS ; 
 int /*<<< orphan*/  STR_ENDSTRING (char*,TYPE_4__) ; 
 int STR_ROTATED ; 
 void* TRUE ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/  open_fp (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
matches_in_list(FILEDESC *list)
{
	char           *sp, *p;
	FILEDESC	*fp;
	int		in_file;
	unsigned char	ch;

	for (fp = list; fp != NULL; fp = fp->next) {
		if (fp->child != NULL) {
			matches_in_list(fp->child);
			continue;
		}
		DPRINTF(1, (stderr, "searching in %s\n", fp->path));
		open_fp(fp);
		sp = Fortbuf;
		in_file = FALSE;
		while (fgets(sp, Fort_len, fp->inf) != NULL)
			if (fp->tbl.str_flags & STR_COMMENTS
			    && sp[0] == fp->tbl.str_delim
			    && sp[1] == fp->tbl.str_delim)
				continue;
			else if (!STR_ENDSTRING(sp, fp->tbl))
				sp += strlen(sp);
			else {
				*sp = '\0';
				if (fp->tbl.str_flags & STR_ROTATED)
					for (p = Fortbuf; (ch = *p) != '\0'; ++p) {
						if (isascii(ch)) {
							if (isupper(ch))
								*p = 'A' + (ch - 'A' + 13) % 26;
							else if (islower(ch))
								*p = 'a' + (ch - 'a' + 13) % 26;
						}
					}
				if (regexec(&Re_pat, Fortbuf, 0, NULL, 0) != REG_NOMATCH) {
					printf("%c%c", fp->tbl.str_delim,
					    fp->tbl.str_delim);
					if (!in_file) {
						printf(" (%s)", fp->name);
						Found_one = TRUE;
						in_file = TRUE;
					}
					putchar('\n');
					(void) fwrite(Fortbuf, 1, (sp - Fortbuf), stdout);
				}
				sp = Fortbuf;
			}
	}
}