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
struct TYPE_5__ {TYPE_4__ tbl; int /*<<< orphan*/  inf; } ;
typedef  TYPE_1__ FILEDESC ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ Fort_len ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int STR_COMMENTS ; 
 int /*<<< orphan*/  STR_ENDSTRING (char*,TYPE_4__) ; 
 int STR_ROTATED ; 
 int /*<<< orphan*/ * Seekpts ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/  open_fp (TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
display(FILEDESC *fp)
{
	char   *p;
	unsigned char ch;
	char	line[BUFSIZ];

	open_fp(fp);
	fseeko(fp->inf, Seekpts[0], SEEK_SET);
	for (Fort_len = 0; fgets(line, sizeof line, fp->inf) != NULL &&
	    !STR_ENDSTRING(line, fp->tbl); Fort_len++) {
		if (fp->tbl.str_flags & STR_ROTATED)
			for (p = line; (ch = *p) != '\0'; ++p) {
				if (isascii(ch)) {
					if (isupper(ch))
						*p = 'A' + (ch - 'A' + 13) % 26;
					else if (islower(ch))
						*p = 'a' + (ch - 'a' + 13) % 26;
				}
			}
		if (fp->tbl.str_flags & STR_COMMENTS
		    && line[0] == fp->tbl.str_delim
		    && line[1] == fp->tbl.str_delim)
			continue;
		fputs(line, stdout);
	}
	(void) fflush(stdout);
}