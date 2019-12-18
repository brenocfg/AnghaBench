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
 int /*<<< orphan*/  EINVAL ; 
 char* __findenv (char const*,int,int*) ; 
 char** environ ; 
 int /*<<< orphan*/  errno ; 
 char** lastenv ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char**,char**,size_t) ; 
 scalar_t__ realloc (char**,int) ; 
 int strlen (char const*) ; 

int
setenv(const char *name, const char *value, int rewrite)
{
	char *C, **P;
	const char *np;
	int l_value, offset = 0;

	for (np = name; *np && *np != '='; ++np)
		;
#ifdef notyet
	if (*np) {
		errno = EINVAL;
		return (-1);			/* has `=' in name */
	}
#endif

	l_value = strlen(value);
	if ((C = __findenv(name, (int)(np - name), &offset)) != NULL) {
		int tmpoff = offset + 1;
		if (!rewrite)
			return (0);
#if 0 /* XXX - existing entry may not be writable */
		if (strlen(C) >= l_value) {	/* old larger; copy over */
			while ((*C++ = *value++))
				;
			return (0);
		}
#endif
		/* could be set multiple times */
		while (__findenv(name, (int)(np - name), &tmpoff)) {
			for (P = &environ[tmpoff];; ++P)
				if (!(*P = *(P + 1)))
					break;
		}
	} else {					/* create new slot */
		size_t cnt;

		for (P = environ; *P != NULL; P++)
			;
		cnt = P - environ;
		P = (char **)realloc(lastenv, sizeof(char *) * (cnt + 2));
		if (!P)
			return (-1);
		if (lastenv != environ)
			memcpy(P, environ, cnt * sizeof(char *));
		lastenv = environ = P;
		offset = cnt;
		environ[cnt + 1] = NULL;
	}
	if (!(environ[offset] =			/* name + `=' + value */
	    malloc((size_t)((int)(np - name) + l_value + 2))))
		return (-1);
	for (C = environ[offset]; (*C = *name++) && *C != '='; ++C)
		;
	for (*C++ = '='; (*C++ = *value++); )
		;
	return (0);
}