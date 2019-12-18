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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
pathcat(const char *prefix, const char *path)
{
	char *str;
	size_t prelen, len;

	prelen = prefix ? strlen(prefix) + 1 : 0;
	len = strlen(path) + 1;
	if ((str = malloc(prelen + len)) == NULL) {
		errno = ENOMEM;
		error("malloc()");
	}
	if (prefix) {
		memcpy(str, prefix, prelen);	/* includes zero */
		str[prelen - 1] = '/';		/* splat zero */
	}
	memcpy(str + prelen, path, len);	/* includes zero */

	return (str);
}