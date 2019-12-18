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
 int ENOMEM ; 
 char** calloc (int,int) ; 
 int setpath (char**,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
setmultipath(char ***what, char *val)
{
	char *s, *v;
	int count, error, idx;

	count = 0;
	v = val;
	do {
		count++;
		s = strchr(v, ',');
		v = (s == NULL) ? NULL : s + 1;
	} while (v != NULL);

	*what = calloc(count + 1, sizeof(char *));
	if (*what == NULL)
		return (ENOMEM);

	for (idx = 0; idx < count; idx++) {
		s = strchr(val, ',');
		if (s != NULL)
			*s++ = '\0';
		error = setpath(*what + idx, val);
		if (error)
			return (error);
		val = s;
	}

	return (0);
}