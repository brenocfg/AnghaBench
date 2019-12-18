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
 char* getenv (char const*) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getenv_int(const char *var, int def)
{
	const char *cp;
	char *ep;
	long val;

	val = def;
	cp = getenv(var);
	if (cp && *cp) {
		val = strtol(cp, &ep, 0);
		if ((ep && *ep) || val != (int)val) {
			val = def;
		}
	}
	return (int)val;
}