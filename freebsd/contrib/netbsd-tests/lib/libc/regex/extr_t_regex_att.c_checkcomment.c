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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static void
checkcomment(const char *s, size_t lineno)
{
	if (s && strstr(s, "BUG") != NULL)
		fprintf(stderr, "Expected %s at line %zu\n", s, lineno);
}