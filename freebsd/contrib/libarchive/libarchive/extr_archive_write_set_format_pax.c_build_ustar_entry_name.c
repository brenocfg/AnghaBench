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
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static char *
build_ustar_entry_name(char *dest, const char *src, size_t src_length,
    const char *insert)
{
	const char *prefix, *prefix_end;
	const char *suffix, *suffix_end;
	const char *filename, *filename_end;
	char *p;
	int need_slash = 0; /* Was there a trailing slash? */
	size_t suffix_length = 99;
	size_t insert_length;

	/* Length of additional dir element to be added. */
	if (insert == NULL)
		insert_length = 0;
	else
		/* +2 here allows for '/' before and after the insert. */
		insert_length = strlen(insert) + 2;

	/* Step 0: Quick bailout in a common case. */
	if (src_length < 100 && insert == NULL) {
		strncpy(dest, src, src_length);
		dest[src_length] = '\0';
		return (dest);
	}

	/* Step 1: Locate filename and enforce the length restriction. */
	filename_end = src + src_length;
	/* Remove trailing '/' chars and '/.' pairs. */
	for (;;) {
		if (filename_end > src && filename_end[-1] == '/') {
			filename_end --;
			need_slash = 1; /* Remember to restore trailing '/'. */
			continue;
		}
		if (filename_end > src + 1 && filename_end[-1] == '.'
		    && filename_end[-2] == '/') {
			filename_end -= 2;
			need_slash = 1; /* "foo/." will become "foo/" */
			continue;
		}
		break;
	}
	if (need_slash)
		suffix_length--;
	/* Find start of filename. */
	filename = filename_end - 1;
	while ((filename > src) && (*filename != '/'))
		filename --;
	if ((*filename == '/') && (filename < filename_end - 1))
		filename ++;
	/* Adjust filename_end so that filename + insert fits in 99 chars. */
	suffix_length -= insert_length;
	if (filename_end > filename + suffix_length)
		filename_end = filename + suffix_length;
	/* Calculate max size for "suffix" section (#3 above). */
	suffix_length -= filename_end - filename;

	/* Step 2: Locate the "prefix" section of the dirname, including
	 * trailing '/'. */
	prefix = src;
	prefix_end = prefix + 155;
	if (prefix_end > filename)
		prefix_end = filename;
	while (prefix_end > prefix && *prefix_end != '/')
		prefix_end--;
	if ((prefix_end < filename) && (*prefix_end == '/'))
		prefix_end++;

	/* Step 3: Locate the "suffix" section of the dirname,
	 * including trailing '/'. */
	suffix = prefix_end;
	suffix_end = suffix + suffix_length; /* Enforce limit. */
	if (suffix_end > filename)
		suffix_end = filename;
	if (suffix_end < suffix)
		suffix_end = suffix;
	while (suffix_end > suffix && *suffix_end != '/')
		suffix_end--;
	if ((suffix_end < filename) && (*suffix_end == '/'))
		suffix_end++;

	/* Step 4: Build the new name. */
	/* The OpenBSD strlcpy function is safer, but less portable. */
	/* Rather than maintain two versions, just use the strncpy version. */
	p = dest;
	if (prefix_end > prefix) {
		strncpy(p, prefix, prefix_end - prefix);
		p += prefix_end - prefix;
	}
	if (suffix_end > suffix) {
		strncpy(p, suffix, suffix_end - suffix);
		p += suffix_end - suffix;
	}
	if (insert != NULL) {
		/* Note: assume insert does not have leading or trailing '/' */
		strcpy(p, insert);
		p += strlen(insert);
		*p++ = '/';
	}
	strncpy(p, filename, filename_end - filename);
	p += filename_end - filename;
	if (need_slash)
		*p++ = '/';
	*p = '\0';

	return (dest);
}