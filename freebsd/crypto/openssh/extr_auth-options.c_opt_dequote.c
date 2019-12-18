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
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *
opt_dequote(const char **sp, const char **errstrp)
{
	const char *s = *sp;
	char *ret;
	size_t i;

	*errstrp = NULL;
	if (*s != '"') {
		*errstrp = "missing start quote";
		return NULL;
	}
	s++;
	if ((ret = malloc(strlen((s)) + 1)) == NULL) {
		*errstrp = "memory allocation failed";
		return NULL;
	}
	for (i = 0; *s != '\0' && *s != '"';) {
		if (s[0] == '\\' && s[1] == '"')
			s++;
		ret[i++] = *s++;
	}
	if (*s == '\0') {
		*errstrp = "missing end quote";
		free(ret);
		return NULL;
	}
	ret[i] = '\0';
	s++;
	*sp = s;
	return ret;
}