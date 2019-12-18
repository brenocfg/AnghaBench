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
typedef  int /*<<< orphan*/  environment ;

/* Variables and functions */
 char EVUTIL_TOUPPER_ (char) ; 
 int /*<<< orphan*/ * evutil_getenv_ (char*) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
event_is_method_disabled(const char *name)
{
	char environment[64];
	int i;

	evutil_snprintf(environment, sizeof(environment), "EVENT_NO%s", name);
	for (i = 8; environment[i] != '\0'; ++i)
		environment[i] = EVUTIL_TOUPPER_(environment[i]);
	/* Note that evutil_getenv_() ignores the environment entirely if
	 * we're setuid */
	return (evutil_getenv_(environment) != NULL);
}