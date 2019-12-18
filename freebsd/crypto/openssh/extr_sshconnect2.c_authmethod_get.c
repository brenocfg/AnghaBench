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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {char* preferred_authentications; } ;
typedef  int /*<<< orphan*/  Authmethod ;

/* Variables and functions */
 scalar_t__ authmethod_is_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * authmethod_lookup (char*) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  debug3 (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* match_list (char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ options ; 
 char* preferred ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* supported ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static Authmethod *
authmethod_get(char *authlist)
{
	char *name = NULL;
	u_int next;

	/* Use a suitable default if we're passed a nil list.  */
	if (authlist == NULL || strlen(authlist) == 0)
		authlist = options.preferred_authentications;

	if (supported == NULL || strcmp(authlist, supported) != 0) {
		debug3("start over, passed a different list %s", authlist);
		free(supported);
		supported = xstrdup(authlist);
		preferred = options.preferred_authentications;
		debug3("preferred %s", preferred);
		current = NULL;
	} else if (current != NULL && authmethod_is_enabled(current))
		return current;

	for (;;) {
		if ((name = match_list(preferred, supported, &next)) == NULL) {
			debug("No more authentication methods to try.");
			current = NULL;
			return NULL;
		}
		preferred += next;
		debug3("authmethod_lookup %s", name);
		debug3("remaining preferred: %s", preferred);
		if ((current = authmethod_lookup(name)) != NULL &&
		    authmethod_is_enabled(current)) {
			debug3("authmethod_is_enabled %s", name);
			debug("Next authentication method: %s", name);
			free(name);
			return current;
		}
		free(name);
	}
}