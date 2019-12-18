#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; int /*<<< orphan*/  cmp; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  error_errno (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  maildir_filename_cmp ; 
 scalar_t__ populate_maildir_list (struct string_list*,char const*) ; 
 int /*<<< orphan*/  split_one (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strbuf_getwholeline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 char* xstrfmt (char*,char const*,int,...) ; 

__attribute__((used)) static int split_maildir(const char *maildir, const char *dir,
	int nr_prec, int skip)
{
	char *file = NULL;
	FILE *f = NULL;
	int ret = -1;
	int i;
	struct string_list list = STRING_LIST_INIT_DUP;

	list.cmp = maildir_filename_cmp;

	if (populate_maildir_list(&list, maildir) < 0)
		goto out;

	for (i = 0; i < list.nr; i++) {
		char *name;

		free(file);
		file = xstrfmt("%s/%s", maildir, list.items[i].string);

		f = fopen(file, "r");
		if (!f) {
			error_errno("cannot open mail %s", file);
			goto out;
		}

		if (strbuf_getwholeline(&buf, f, '\n')) {
			error_errno("cannot read mail %s", file);
			goto out;
		}

		name = xstrfmt("%s/%0*d", dir, nr_prec, ++skip);
		split_one(f, name, 1);
		free(name);

		fclose(f);
		f = NULL;
	}

	ret = skip;
out:
	if (f)
		fclose(f);
	free(file);
	string_list_clear(&list, 1);
	return ret;
}