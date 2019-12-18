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
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
command_alias(const char *name)
{
    const char *aliases[] = {
	"kinit", "klist", "kswitch", "kgetcred", "kvno", "kdeltkt",
	"kdestroy", "kcpytkt", NULL
    }, **p = aliases;

    while (*p && strcmp(name, *p) != 0)
	p++;
    return *p != NULL;
}