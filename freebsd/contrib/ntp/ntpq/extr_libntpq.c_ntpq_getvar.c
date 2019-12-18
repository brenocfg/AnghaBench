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
 scalar_t__ nextvar (size_t*,char const**,char**,char**) ; 
 int /*<<< orphan*/  ntpq_stripquotes (char*,char*,size_t,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char*) ; 

size_t
ntpq_getvar(
	const char *	resultbuf,
	size_t		datalen,
	const char *	varname,
	char *		varvalue,
	size_t		maxlen)
{
	char *	name;
	char *	value;
	size_t	idatalen;

	value = NULL;
	idatalen = (int)datalen;

	while (nextvar(&idatalen, &resultbuf, &name, &value)) {
		if (strcmp(varname, name) == 0) {
			ntpq_stripquotes(varvalue, value, strlen(value), maxlen);

			return strlen(varvalue);
		}
	}

	return 0;
}