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
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {char* util; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ parse_key_value_squoted (int /*<<< orphan*/ ,struct string_list*) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 

int read_author_script(const char *path, char **name, char **email, char **date,
		       int allow_missing)
{
	struct strbuf buf = STRBUF_INIT;
	struct string_list kv = STRING_LIST_INIT_DUP;
	int retval = -1; /* assume failure */
	int i, name_i = -2, email_i = -2, date_i = -2, err = 0;

	if (strbuf_read_file(&buf, path, 256) <= 0) {
		strbuf_release(&buf);
		if (errno == ENOENT && allow_missing)
			return 0;
		else
			return error_errno(_("could not open '%s' for reading"),
					   path);
	}

	if (parse_key_value_squoted(buf.buf, &kv))
		goto finish;

	for (i = 0; i < kv.nr; i++) {
		if (!strcmp(kv.items[i].string, "GIT_AUTHOR_NAME")) {
			if (name_i != -2)
				name_i = error(_("'GIT_AUTHOR_NAME' already given"));
			else
				name_i = i;
		} else if (!strcmp(kv.items[i].string, "GIT_AUTHOR_EMAIL")) {
			if (email_i != -2)
				email_i = error(_("'GIT_AUTHOR_EMAIL' already given"));
			else
				email_i = i;
		} else if (!strcmp(kv.items[i].string, "GIT_AUTHOR_DATE")) {
			if (date_i != -2)
				date_i = error(_("'GIT_AUTHOR_DATE' already given"));
			else
				date_i = i;
		} else {
			err = error(_("unknown variable '%s'"),
				    kv.items[i].string);
		}
	}
	if (name_i == -2)
		error(_("missing 'GIT_AUTHOR_NAME'"));
	if (email_i == -2)
		error(_("missing 'GIT_AUTHOR_EMAIL'"));
	if (date_i == -2)
		error(_("missing 'GIT_AUTHOR_DATE'"));
	if (date_i < 0 || email_i < 0 || date_i < 0 || err)
		goto finish;
	*name = kv.items[name_i].util;
	*email = kv.items[email_i].util;
	*date = kv.items[date_i].util;
	retval = 0;
finish:
	string_list_clear(&kv, !!retval);
	strbuf_release(&buf);
	return retval;
}