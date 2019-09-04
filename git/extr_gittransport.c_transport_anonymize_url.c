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
 int /*<<< orphan*/  isalnum (char const) ; 
 void* strchr (char const*,char) ; 
 size_t strlen (char*) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ url_is_local_not_ssh (char const*) ; 
 char* xstrdup (char const*) ; 
 char* xstrfmt (char*,int,char const*,int,char*) ; 

char *transport_anonymize_url(const char *url)
{
	char *scheme_prefix, *anon_part;
	size_t anon_len, prefix_len = 0;

	anon_part = strchr(url, '@');
	if (url_is_local_not_ssh(url) || !anon_part)
		goto literal_copy;

	anon_len = strlen(++anon_part);
	scheme_prefix = strstr(url, "://");
	if (!scheme_prefix) {
		if (!strchr(anon_part, ':'))
			/* cannot be "me@there:/path/name" */
			goto literal_copy;
	} else {
		const char *cp;
		/* make sure scheme is reasonable */
		for (cp = url; cp < scheme_prefix; cp++) {
			switch (*cp) {
				/* RFC 1738 2.1 */
			case '+': case '.': case '-':
				break; /* ok */
			default:
				if (isalnum(*cp))
					break;
				/* it isn't */
				goto literal_copy;
			}
		}
		/* @ past the first slash does not count */
		cp = strchr(scheme_prefix + 3, '/');
		if (cp && cp < anon_part)
			goto literal_copy;
		prefix_len = scheme_prefix - url + 3;
	}
	return xstrfmt("%.*s%.*s", (int)prefix_len, url,
		       (int)anon_len, anon_part);
literal_copy:
	return xstrdup(url);
}