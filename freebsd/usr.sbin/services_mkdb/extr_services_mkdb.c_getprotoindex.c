#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t sl_cur; int /*<<< orphan*/ * sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 size_t PROTOMAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static size_t
getprotoindex(StringList *sl, const char *str)
{
	size_t i;
	char *p;

	for (i= 0; i < sl->sl_cur; i++)
		if (strcmp(sl->sl_str[i], str) == 0)
			return i;

	if (i == PROTOMAX)
		errx(1, "Ran out of protocols adding `%s';"
		    " recompile with larger PROTOMAX", str);
	if ((p = strdup(str)) == NULL)
		err(1, "Cannot copy string");
	(void)sl_add(sl, p);
	return i;
}