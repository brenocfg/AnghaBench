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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  error_errno (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (int) ; 
 int split_one (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strbuf_getwholeline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 
 char* xstrfmt (char*,char const*,int,int) ; 

__attribute__((used)) static int split_mbox(const char *file, const char *dir, int allow_bare,
		      int nr_prec, int skip)
{
	int ret = -1;
	int peek;

	FILE *f = !strcmp(file, "-") ? stdin : fopen(file, "r");
	int file_done = 0;

	if (!f) {
		error_errno("cannot open mbox %s", file);
		goto out;
	}

	do {
		peek = fgetc(f);
		if (peek == EOF) {
			if (f == stdin)
				/* empty stdin is OK */
				ret = skip;
			else {
				fclose(f);
				error(_("empty mbox: '%s'"), file);
			}
			goto out;
		}
	} while (isspace(peek));
	ungetc(peek, f);

	if (strbuf_getwholeline(&buf, f, '\n')) {
		/* empty stdin is OK */
		if (f != stdin) {
			error("cannot read mbox %s", file);
			goto out;
		}
		file_done = 1;
	}

	while (!file_done) {
		char *name = xstrfmt("%s/%0*d", dir, nr_prec, ++skip);
		file_done = split_one(f, name, allow_bare);
		free(name);
	}

	if (f != stdin)
		fclose(f);

	ret = skip;
out:
	return ret;
}