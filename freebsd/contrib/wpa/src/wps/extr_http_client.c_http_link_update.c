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
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  os_snprintf (char*,size_t,char*,char const*,char*) ; 
 char* os_strchr (char const*,char) ; 
 int os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 char* os_strrchr (char const*,char) ; 

char * http_link_update(char *url, const char *base)
{
	char *n;
	size_t len;
	const char *pos;

	/* RFC 2396, Chapter 5.2 */
	/* TODO: consider adding all cases described in RFC 2396 */

	if (url == NULL)
		return NULL;

	if (os_strncmp(url, "http://", 7) == 0)
		return url; /* absolute link */

	if (os_strncmp(base, "http://", 7) != 0)
		return url; /* unable to handle base URL */

	len = os_strlen(url) + 1 + os_strlen(base) + 1;
	n = os_malloc(len);
	if (n == NULL)
		return url; /* failed */

	if (url[0] == '/') {
		pos = os_strchr(base + 7, '/');
		if (pos == NULL) {
			os_snprintf(n, len, "%s%s", base, url);
		} else {
			os_memcpy(n, base, pos - base);
			os_memcpy(n + (pos - base), url, os_strlen(url) + 1);
		}
	} else {
		pos = os_strrchr(base + 7, '/');
		if (pos == NULL) {
			os_snprintf(n, len, "%s/%s", base, url);
		} else {
			os_memcpy(n, base, pos - base + 1);
			os_memcpy(n + (pos - base) + 1, url, os_strlen(url) +
				  1);
		}
	}

	os_free(url);

	return n;
}