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
typedef  char u_char ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  isalnum (char) ; 
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 
 char tolower (char) ; 

int
valid_domain(char *name, int makelower, const char **errstr)
{
	size_t i, l = strlen(name);
	u_char c, last = '\0';
	static char errbuf[256];

	if (l == 0) {
		strlcpy(errbuf, "empty domain name", sizeof(errbuf));
		goto bad;
	}
	if (!isalpha((u_char)name[0]) && !isdigit((u_char)name[0])) {
		snprintf(errbuf, sizeof(errbuf), "domain name \"%.100s\" "
		    "starts with invalid character", name);
		goto bad;
	}
	for (i = 0; i < l; i++) {
		c = tolower((u_char)name[i]);
		if (makelower)
			name[i] = (char)c;
		if (last == '.' && c == '.') {
			snprintf(errbuf, sizeof(errbuf), "domain name "
			    "\"%.100s\" contains consecutive separators", name);
			goto bad;
		}
		if (c != '.' && c != '-' && !isalnum(c) &&
		    c != '_') /* technically invalid, but common */ {
			snprintf(errbuf, sizeof(errbuf), "domain name "
			    "\"%.100s\" contains invalid characters", name);
			goto bad;
		}
		last = c;
	}
	if (name[l - 1] == '.')
		name[l - 1] = '\0';
	if (errstr != NULL)
		*errstr = NULL;
	return 1;
bad:
	if (errstr != NULL)
		*errstr = errbuf;
	return 0;
}