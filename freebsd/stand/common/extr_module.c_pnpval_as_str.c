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
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  quoted_strcpy (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static char *
pnpval_as_str(const char *val, const char *pnpinfo)
{
	static char retval[256];
	char key[256];
	char *cp;

	if (pnpinfo == NULL) {
		*retval = '\0';
		return retval;
	}

	cp = strchr(val, ';');
	key[0] = ' ';
	if (cp == NULL)
		strlcpy(key + 1, val, sizeof(key) - 1);
	else {
		memcpy(key + 1, val, cp - val);
		key[cp - val + 1] = '\0';
	}
	strlcat(key, "=", sizeof(key));
	if (strncmp(key + 1, pnpinfo, strlen(key + 1)) == 0)
		quoted_strcpy(retval, pnpinfo + strlen(key + 1));
	else {
		cp = strstr(pnpinfo, key);
		if (cp == NULL)
			strcpy(retval, "MISSING");
		else
			quoted_strcpy(retval, cp + strlen(key));
	}
	return retval;
}