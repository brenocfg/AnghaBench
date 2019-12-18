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
 int TTY_IFCONSOLE ; 
 int TTY_ON ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
auto_tty_status(const char *ty_name)
{
	size_t len;
	char *buf, *cons, *nextcons;
	int rv;

	rv = TTY_IFCONSOLE;

	/* Check if this is an enabled kernel console line */
	buf = NULL;
	if (sysctlbyname("kern.console", NULL, &len, NULL, 0) == -1)
		return (rv); /* Errors mean don't enable */
	buf = malloc(len);
	if (sysctlbyname("kern.console", buf, &len, NULL, 0) == -1)
		goto done;

	if ((cons = strchr(buf, '/')) == NULL)
		goto done;
	*cons = '\0';
	nextcons = buf;
	while ((cons = strsep(&nextcons, ",")) != NULL && strlen(cons) != 0) {
		if (strcmp(cons, ty_name) == 0) {
			rv |= TTY_ON;
			break;
		}
	}

done:
	free(buf);
	return (rv);
}