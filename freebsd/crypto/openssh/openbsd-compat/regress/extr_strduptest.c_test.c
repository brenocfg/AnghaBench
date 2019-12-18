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
 int fail ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 

void
test(const char *a)
{
	char *b;

	b = strdup(a);
	if (b == 0) {
		fail = 1;
		return;
	}
	if (strcmp(a, b) != 0)
		fail = 1;
	free(b);
}