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
 int /*<<< orphan*/  ED (char*,char const*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void
add_to(const char ** v, int l, const char *arg, const char *msg)
{
	for (; l > 0 && *v != NULL ; l--, v++);
	if (l == 0) {
		ED("%s %s", msg, arg);
		exit(1);
	}
	*v = arg;
}