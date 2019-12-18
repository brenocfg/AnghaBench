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
struct option {char* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,...) ; 
 struct option* getoption (char const*) ; 

char *
getoptionvalue(const char *name)
{
	struct option *c;

	if (name == NULL)
		errx(1, "getoptionvalue: invoked with NULL name");
	c = getoption(name);
	if (c != NULL)
		return (c->value);
	errx(1, "getoptionvalue: invoked with unknown option `%s'", name);
	/* NOTREACHED */
}