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
 char* getenv (char*) ; 
 scalar_t__ strlen (char const*) ; 

int use_gettext_poison(void)
{
	static int poison_requested = -1;
	if (poison_requested == -1) {
		const char *v = getenv("GIT_TEST_GETTEXT_POISON");
		poison_requested = v && strlen(v) ? 1 : 0;
	}
	return poison_requested;
}