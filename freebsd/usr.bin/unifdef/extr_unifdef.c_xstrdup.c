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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static const char *
xstrdup(const char *start, const char *end)
{
	size_t n;
	char *s;

	if (end < start) abort(); /* bug */
	n = (size_t)(end - start) + 1;
	s = malloc(n);
	if (s == NULL)
		err(2, "malloc");
	snprintf(s, n, "%s", start);
	return (s);
}