#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {scalar_t__* enabled; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__** authmethods ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 char* xstrdup (char const*) ; 

int
auth2_methods_valid(const char *_methods, int need_enable)
{
	char *methods, *omethods, *method, *p;
	u_int i, found;
	int ret = -1;

	if (*_methods == '\0') {
		error("empty authentication method list");
		return -1;
	}
	omethods = methods = xstrdup(_methods);
	while ((method = strsep(&methods, ",")) != NULL) {
		for (found = i = 0; !found && authmethods[i] != NULL; i++) {
			if ((p = strchr(method, ':')) != NULL)
				*p = '\0';
			if (strcmp(method, authmethods[i]->name) != 0)
				continue;
			if (need_enable) {
				if (authmethods[i]->enabled == NULL ||
				    *(authmethods[i]->enabled) == 0) {
					error("Disabled method \"%s\" in "
					    "AuthenticationMethods list \"%s\"",
					    method, _methods);
					goto out;
				}
			}
			found = 1;
			break;
		}
		if (!found) {
			error("Unknown authentication method \"%s\" in list",
			    method);
			goto out;
		}
	}
	ret = 0;
 out:
	free(omethods);
	return ret;
}