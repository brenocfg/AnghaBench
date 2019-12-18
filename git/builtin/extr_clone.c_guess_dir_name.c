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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dir_sep (char const) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/ * memchr (char const*,char,int) ; 
 int /*<<< orphan*/  strip_suffix_mem (char const*,size_t*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 
 char* xstrfmt (char*,int,char const*) ; 
 char* xstrndup (char const*,size_t) ; 

__attribute__((used)) static char *guess_dir_name(const char *repo, int is_bundle, int is_bare)
{
	const char *end = repo + strlen(repo), *start, *ptr;
	size_t len;
	char *dir;

	/*
	 * Skip scheme.
	 */
	start = strstr(repo, "://");
	if (start == NULL)
		start = repo;
	else
		start += 3;

	/*
	 * Skip authentication data. The stripping does happen
	 * greedily, such that we strip up to the last '@' inside
	 * the host part.
	 */
	for (ptr = start; ptr < end && !is_dir_sep(*ptr); ptr++) {
		if (*ptr == '@')
			start = ptr + 1;
	}

	/*
	 * Strip trailing spaces, slashes and /.git
	 */
	while (start < end && (is_dir_sep(end[-1]) || isspace(end[-1])))
		end--;
	if (end - start > 5 && is_dir_sep(end[-5]) &&
	    !strncmp(end - 4, ".git", 4)) {
		end -= 5;
		while (start < end && is_dir_sep(end[-1]))
			end--;
	}

	/*
	 * Strip trailing port number if we've got only a
	 * hostname (that is, there is no dir separator but a
	 * colon). This check is required such that we do not
	 * strip URI's like '/foo/bar:2222.git', which should
	 * result in a dir '2222' being guessed due to backwards
	 * compatibility.
	 */
	if (memchr(start, '/', end - start) == NULL
	    && memchr(start, ':', end - start) != NULL) {
		ptr = end;
		while (start < ptr && isdigit(ptr[-1]) && ptr[-1] != ':')
			ptr--;
		if (start < ptr && ptr[-1] == ':')
			end = ptr - 1;
	}

	/*
	 * Find last component. To remain backwards compatible we
	 * also regard colons as path separators, such that
	 * cloning a repository 'foo:bar.git' would result in a
	 * directory 'bar' being guessed.
	 */
	ptr = end;
	while (start < ptr && !is_dir_sep(ptr[-1]) && ptr[-1] != ':')
		ptr--;
	start = ptr;

	/*
	 * Strip .{bundle,git}.
	 */
	len = end - start;
	strip_suffix_mem(start, &len, is_bundle ? ".bundle" : ".git");

	if (!len || (len == 1 && *start == '/'))
		die(_("No directory name could be guessed.\n"
		      "Please specify a directory on the command line"));

	if (is_bare)
		dir = xstrfmt("%.*s.git", (int)len, start);
	else
		dir = xstrndup(start, len);
	/*
	 * Replace sequences of 'control' characters and whitespace
	 * with one ascii space, remove leading and trailing spaces.
	 */
	if (*dir) {
		char *out = dir;
		int prev_space = 1 /* strip leading whitespace */;
		for (end = dir; *end; ++end) {
			char ch = *end;
			if ((unsigned char)ch < '\x20')
				ch = '\x20';
			if (isspace(ch)) {
				if (prev_space)
					continue;
				prev_space = 1;
			} else
				prev_space = 0;
			*out++ = ch;
		}
		*out = '\0';
		if (out > dir && prev_space)
			out[-1] = '\0';
	}
	return dir;
}