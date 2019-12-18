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
struct cclass {char* name; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  M_CLASS ; 
 struct cclass* cclasses ; 
 char* g_strchr (char const*,char) ; 
 int /*<<< orphan*/  g_strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static int
g_charclass(const Char **patternp, Char **bufnextp)
{
	const Char *pattern = *patternp + 1;
	Char *bufnext = *bufnextp;
	const Char *colon;
	struct cclass *cc;
	size_t len;

	if ((colon = g_strchr(pattern, ':')) == NULL || colon[1] != ']')
		return 1;	/* not a character class */

	len = (size_t)(colon - pattern);
	for (cc = cclasses; cc->name != NULL; cc++) {
		if (!g_strncmp(pattern, cc->name, len) && cc->name[len] == '\0')
			break;
	}
	if (cc->name == NULL)
		return -1;	/* invalid character class */
	*bufnext++ = M_CLASS;
	*bufnext++ = (Char)(cc - &cclasses[0]);
	*bufnextp = bufnext;
	*patternp += len + 3;

	return 0;
}