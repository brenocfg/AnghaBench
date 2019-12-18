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
struct protox {int dummy; } ;
struct protoent {char** p_aliases; char const* p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  endprotoent () ; 
 struct protoent* getprotoent () ; 
 struct protox* knownname (char const*) ; 
 int /*<<< orphan*/  setprotoent (int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct protox *
name2protox(const char *name)
{
	struct protox *tp;
	char **alias;			/* alias from p->aliases */
	struct protoent *p;

	/*
	 * Try to find the name in the list of "well-known" names. If that
	 * fails, check if name is an alias for an Internet protocol.
	 */
	if ((tp = knownname(name)) != NULL)
		return (tp);

	setprotoent(1);			/* make protocol lookup cheaper */
	while ((p = getprotoent()) != NULL) {
		/* assert: name not same as p->name */
		for (alias = p->p_aliases; *alias; alias++)
			if (strcmp(name, *alias) == 0) {
				endprotoent();
				return (knownname(p->p_name));
			}
	}
	endprotoent();
	return (NULL);
}