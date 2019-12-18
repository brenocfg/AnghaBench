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
typedef  int /*<<< orphan*/  pathbuf ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* lm_find (char const*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 char* xmalloc (size_t const) ; 

char *
lm_findn(const char *p, const char *f, const size_t n)
{
	char pathbuf[64], *s, *t;

	if (n < sizeof(pathbuf) - 1)
		s = pathbuf;
	else
		s = xmalloc(n + 1);
	memcpy(s, f, n);
	s[n] = '\0';
	t = lm_find(p, s);
	if (s != pathbuf)
		free(s);
	return (t);
}