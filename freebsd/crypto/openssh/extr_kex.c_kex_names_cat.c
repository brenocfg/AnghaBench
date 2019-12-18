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
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* match_list (char*,char*,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 
 size_t strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* strsep (char**,char*) ; 

char *
kex_names_cat(const char *a, const char *b)
{
	char *ret = NULL, *tmp = NULL, *cp, *p, *m;
	size_t len;

	if (a == NULL || *a == '\0')
		return strdup(b);
	if (b == NULL || *b == '\0')
		return strdup(a);
	if (strlen(b) > 1024*1024)
		return NULL;
	len = strlen(a) + strlen(b) + 2;
	if ((tmp = cp = strdup(b)) == NULL ||
	    (ret = calloc(1, len)) == NULL) {
		free(tmp);
		return NULL;
	}
	strlcpy(ret, a, len);
	for ((p = strsep(&cp, ",")); p && *p != '\0'; (p = strsep(&cp, ","))) {
		if ((m = match_list(ret, p, NULL)) != NULL) {
			free(m);
			continue; /* Algorithm already present */
		}
		if (strlcat(ret, ",", len) >= len ||
		    strlcat(ret, p, len) >= len) {
			free(tmp);
			free(ret);
			return NULL; /* Shouldn't happen */
		}
	}
	free(tmp);
	return ret;
}