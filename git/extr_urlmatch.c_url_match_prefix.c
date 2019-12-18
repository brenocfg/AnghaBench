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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static size_t url_match_prefix(const char *url,
			       const char *url_prefix,
			       size_t url_prefix_len)
{
	/*
	 * url_prefix matches url if url_prefix is an exact match for url or it
	 * is a prefix of url and the match ends on a path component boundary.
	 * Both url and url_prefix are considered to have an implicit '/' on the
	 * end for matching purposes if they do not already.
	 *
	 * url must be NUL terminated.  url_prefix_len is the length of
	 * url_prefix which need not be NUL terminated.
	 *
	 * The return value is the length of the match in characters (including
	 * the final '/' even if it's implicit) or 0 for no match.
	 *
	 * Passing NULL as url and/or url_prefix will always cause 0 to be
	 * returned without causing any faults.
	 */
	if (!url || !url_prefix)
		return 0;
	if (!url_prefix_len || (url_prefix_len == 1 && *url_prefix == '/'))
		return (!*url || *url == '/') ? 1 : 0;
	if (url_prefix[url_prefix_len - 1] == '/')
		url_prefix_len--;
	if (strncmp(url, url_prefix, url_prefix_len))
		return 0;
	if ((strlen(url) == url_prefix_len) || (url[url_prefix_len] == '/'))
		return url_prefix_len + 1;
	return 0;
}