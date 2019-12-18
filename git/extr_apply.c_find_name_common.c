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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ isspace (char) ; 
 scalar_t__ name_terminate (char,int) ; 
 char* squash_slash (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 char* xmemdupz (char const*,int) ; 
 char* xstrdup (char const*) ; 
 char* xstrdup_or_null (char const*) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static char *find_name_common(struct strbuf *root,
			      const char *line,
			      const char *def,
			      int p_value,
			      const char *end,
			      int terminate)
{
	int len;
	const char *start = NULL;

	if (p_value == 0)
		start = line;
	while (line != end) {
		char c = *line;

		if (!end && isspace(c)) {
			if (c == '\n')
				break;
			if (name_terminate(c, terminate))
				break;
		}
		line++;
		if (c == '/' && !--p_value)
			start = line;
	}
	if (!start)
		return squash_slash(xstrdup_or_null(def));
	len = line - start;
	if (!len)
		return squash_slash(xstrdup_or_null(def));

	/*
	 * Generally we prefer the shorter name, especially
	 * if the other one is just a variation of that with
	 * something else tacked on to the end (ie "file.orig"
	 * or "file~").
	 */
	if (def) {
		int deflen = strlen(def);
		if (deflen < len && !strncmp(start, def, deflen))
			return squash_slash(xstrdup(def));
	}

	if (root->len) {
		char *ret = xstrfmt("%s%.*s", root->buf, len, start);
		return squash_slash(ret);
	}

	return squash_slash(xmemdupz(start, len));
}